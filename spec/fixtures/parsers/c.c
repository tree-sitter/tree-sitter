#include "tree_sitter/parser.h"

#define STATE_COUNT 400
#define SYMBOL_COUNT 80

enum {
    sym_translation_unit = ts_builtin_sym_start,
    sym_preproc_define,
    sym_function_definition,
    sym_declaration_specifiers,
    sym_storage_class_specifier,
    sym__type_specifier,
    sym_numeric_type_specifier,
    sym_macro_type,
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
    aux_sym_translation_unit_repeat1,
    aux_sym_function_definition_repeat1,
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
    anon_sym_LPAREN,
    anon_sym_RPAREN,
    anon_sym_struct,
    anon_sym_LBRACE,
    anon_sym_RBRACE,
    anon_sym_COMMA,
    anon_sym_SEMI,
    anon_sym_EQ,
    anon_sym_LBRACK,
    anon_sym_RBRACK,
    anon_sym_DOT,
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
    [sym_macro_type] = "macro_type",
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
    [aux_sym_translation_unit_repeat1] = "translation_unit_repeat1",
    [aux_sym_function_definition_repeat1] = "function_definition_repeat1",
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
    [anon_sym_LPAREN] = "(",
    [anon_sym_RPAREN] = ")",
    [anon_sym_struct] = "struct",
    [anon_sym_LBRACE] = "{",
    [anon_sym_RBRACE] = "}",
    [anon_sym_COMMA] = ",",
    [anon_sym_SEMI] = ";",
    [anon_sym_EQ] = "=",
    [anon_sym_LBRACK] = "[",
    [anon_sym_RBRACK] = "]",
    [anon_sym_DOT] = ".",
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

static const TSNodeType ts_node_types[SYMBOL_COUNT] = {
    [sym_translation_unit] = TSNodeTypeNamed,
    [sym_preproc_define] = TSNodeTypeNamed,
    [sym_function_definition] = TSNodeTypeNamed,
    [sym_declaration_specifiers] = TSNodeTypeNamed,
    [sym_storage_class_specifier] = TSNodeTypeNamed,
    [sym__type_specifier] = TSNodeTypeHidden,
    [sym_numeric_type_specifier] = TSNodeTypeNamed,
    [sym_macro_type] = TSNodeTypeNamed,
    [sym_struct_specifier] = TSNodeTypeNamed,
    [sym_type_name] = TSNodeTypeNamed,
    [sym_struct_declaration] = TSNodeTypeNamed,
    [sym_parameter_declaration] = TSNodeTypeNamed,
    [sym_declaration] = TSNodeTypeNamed,
    [sym__init_declarator] = TSNodeTypeHidden,
    [sym_initializer] = TSNodeTypeNamed,
    [sym_initializer_list] = TSNodeTypeNamed,
    [sym_designation] = TSNodeTypeNamed,
    [sym__declarator] = TSNodeTypeHidden,
    [sym__abstract_declarator] = TSNodeTypeHidden,
    [sym_pointer_declarator] = TSNodeTypeNamed,
    [sym_abstract_pointer_declarator] = TSNodeTypeNamed,
    [sym_function_declarator] = TSNodeTypeNamed,
    [sym_abstract_function_declarator] = TSNodeTypeNamed,
    [sym_array_declarator] = TSNodeTypeNamed,
    [sym_abstract_array_declarator] = TSNodeTypeNamed,
    [sym_type_qualifier] = TSNodeTypeNamed,
    [sym_compound_statement] = TSNodeTypeNamed,
    [sym__expression] = TSNodeTypeHidden,
    [sym_cast_expression] = TSNodeTypeNamed,
    [sym_math_expression] = TSNodeTypeNamed,
    [sym_call_expression] = TSNodeTypeNamed,
    [sym_pointer_expression] = TSNodeTypeNamed,
    [sym__statement] = TSNodeTypeHidden,
    [sym_expression_statement] = TSNodeTypeNamed,
    [aux_sym_translation_unit_repeat1] = TSNodeTypeHidden,
    [aux_sym_function_definition_repeat1] = TSNodeTypeHidden,
    [aux_sym_declaration_specifiers_repeat1] = TSNodeTypeHidden,
    [aux_sym_numeric_type_specifier_repeat1] = TSNodeTypeHidden,
    [aux_sym_struct_specifier_repeat1] = TSNodeTypeHidden,
    [aux_sym_type_name_repeat1] = TSNodeTypeHidden,
    [aux_sym_declaration_repeat1] = TSNodeTypeHidden,
    [aux_sym_designation_repeat1] = TSNodeTypeHidden,
    [aux_sym_function_declarator_repeat1] = TSNodeTypeHidden,
    [aux_sym_compound_statement_repeat1] = TSNodeTypeHidden,
    [aux_sym_call_expression_repeat1] = TSNodeTypeHidden,
    [ts_builtin_sym_error] = TSNodeTypeNamed,
    [ts_builtin_sym_end] = TSNodeTypeHidden,
    [anon_sym_POUNDdefine] = TSNodeTypeAnonymous,
    [anon_sym_LF] = TSNodeTypeAnonymous,
    [sym_preproc_arg] = TSNodeTypeNamed,
    [anon_sym_typedef] = TSNodeTypeAnonymous,
    [anon_sym_extern] = TSNodeTypeAnonymous,
    [anon_sym_static] = TSNodeTypeAnonymous,
    [anon_sym_auto] = TSNodeTypeAnonymous,
    [anon_sym_register] = TSNodeTypeAnonymous,
    [anon_sym_signed] = TSNodeTypeAnonymous,
    [anon_sym_unsigned] = TSNodeTypeAnonymous,
    [anon_sym_long] = TSNodeTypeAnonymous,
    [anon_sym_short] = TSNodeTypeAnonymous,
    [anon_sym_LPAREN] = TSNodeTypeAnonymous,
    [anon_sym_RPAREN] = TSNodeTypeAnonymous,
    [anon_sym_struct] = TSNodeTypeAnonymous,
    [anon_sym_LBRACE] = TSNodeTypeAnonymous,
    [anon_sym_RBRACE] = TSNodeTypeAnonymous,
    [anon_sym_COMMA] = TSNodeTypeAnonymous,
    [anon_sym_SEMI] = TSNodeTypeAnonymous,
    [anon_sym_EQ] = TSNodeTypeAnonymous,
    [anon_sym_LBRACK] = TSNodeTypeAnonymous,
    [anon_sym_RBRACK] = TSNodeTypeAnonymous,
    [anon_sym_DOT] = TSNodeTypeAnonymous,
    [anon_sym_STAR] = TSNodeTypeAnonymous,
    [anon_sym_const] = TSNodeTypeAnonymous,
    [anon_sym_restrict] = TSNodeTypeAnonymous,
    [anon_sym_volatile] = TSNodeTypeAnonymous,
    [anon_sym_PLUS] = TSNodeTypeAnonymous,
    [anon_sym_AMP] = TSNodeTypeAnonymous,
    [sym_string] = TSNodeTypeNamed,
    [sym_identifier] = TSNodeTypeNamed,
    [sym_number] = TSNodeTypeNamed,
    [sym_comment] = TSNodeTypeNamed,
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
            if (lookahead == ';')
                ADVANCE(99);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 97:
            ACCEPT_TOKEN(anon_sym_LPAREN);
        case 98:
            ACCEPT_TOKEN(anon_sym_STAR);
        case 99:
            ACCEPT_TOKEN(anon_sym_SEMI);
        case 100:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 101:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
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
                ADVANCE(102);
            if (lookahead == 'u')
                ADVANCE(75);
            LEX_ERROR();
        case 102:
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
        case 103:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '{')
                ADVANCE(104);
            LEX_ERROR();
        case 104:
            ACCEPT_TOKEN(anon_sym_LBRACE);
        case 105:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(105);
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 107:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
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
                ADVANCE(109);
            LEX_ERROR();
        case 109:
            ACCEPT_TOKEN(anon_sym_RBRACE);
        case 110:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '{')
                ADVANCE(104);
            LEX_ERROR();
        case 111:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(111);
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
                ADVANCE(109);
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
                ADVANCE(109);
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
            if (lookahead == ')')
                ADVANCE(106);
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
        case 116:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == ']')
                ADVANCE(125);
            LEX_ERROR();
        case 117:
            if (lookahead == '\"')
                ADVANCE(118);
            if (lookahead == '\\')
                ADVANCE(119);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(117);
            LEX_ERROR();
        case 118:
            ACCEPT_TOKEN(sym_string);
        case 119:
            if (lookahead == '\"')
                ADVANCE(120);
            if (lookahead == '\\')
                ADVANCE(119);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(117);
            LEX_ERROR();
        case 120:
            if (lookahead == '\"')
                ADVANCE(118);
            if (lookahead == '\\')
                ADVANCE(119);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(117);
            ACCEPT_TOKEN(sym_string);
        case 121:
            ACCEPT_TOKEN(anon_sym_AMP);
        case 122:
            if (lookahead == '.')
                ADVANCE(123);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            ACCEPT_TOKEN(sym_number);
        case 123:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(124);
            LEX_ERROR();
        case 124:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(124);
            ACCEPT_TOKEN(sym_number);
        case 125:
            ACCEPT_TOKEN(anon_sym_RBRACK);
        case 126:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ']')
                ADVANCE(125);
            LEX_ERROR();
        case 127:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 128:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
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
                ADVANCE(129);
            if (lookahead == 's')
                ADVANCE(93);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            LEX_ERROR();
        case 129:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(130);
            ACCEPT_TOKEN(sym_identifier);
        case 130:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(43);
            ACCEPT_TOKEN(sym_identifier);
        case 131:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(131);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 132:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(127);
            if (lookahead == ',')
                ADVANCE(134);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 134:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
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
                ADVANCE(129);
            if (lookahead == 's')
                ADVANCE(93);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
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
                ADVANCE(106);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(127);
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
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(114);
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
            if (lookahead == '*')
                ADVANCE(98);
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
                ADVANCE(106);
            if (lookahead == '*')
                ADVANCE(98);
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
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == ',')
                ADVANCE(134);
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
                ADVANCE(106);
            if (lookahead == ',')
                ADVANCE(134);
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
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(151);
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
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(151);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 145:
            if (lookahead == '*')
                ADVANCE(146);
            if (lookahead == '/')
                ADVANCE(154);
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(151);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 146:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '*')
                ADVANCE(147);
            if (lookahead == '\\')
                ADVANCE(152);
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
                ADVANCE(152);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(146);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 148:
            if (lookahead == '\\')
                ADVANCE(149);
            ACCEPT_TOKEN(sym_comment);
        case 149:
            if (lookahead == '\n')
                ADVANCE(150);
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(151);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 150:
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(151);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 151:
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(151);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 152:
            if (lookahead == '\n')
                ADVANCE(153);
            if (lookahead == '*')
                ADVANCE(147);
            if (lookahead == '\\')
                ADVANCE(152);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(146);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 153:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '*')
                ADVANCE(147);
            if (lookahead == '\\')
                ADVANCE(152);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(146);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 154:
            if (lookahead == '\\')
                ADVANCE(155);
            ACCEPT_TOKEN(sym_comment);
        case 155:
            if (lookahead == '\\')
                ADVANCE(155);
            ACCEPT_TOKEN(sym_comment);
        case 156:
            START_TOKEN();
            if (lookahead == '/')
                ADVANCE(145);
            if (lookahead == '\\')
                ADVANCE(149);
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
            if (lookahead == '/')
                ADVANCE(10);
            ACCEPT_TOKEN(anon_sym_LF);
        case 159:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == ',')
                ADVANCE(134);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(99);
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
                ADVANCE(134);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(99);
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
                ADVANCE(104);
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
            if (lookahead == '{')
                ADVANCE(104);
            LEX_ERROR();
        case 163:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(163);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
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
                ADVANCE(109);
            LEX_ERROR();
        case 164:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(164);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '{')
                ADVANCE(104);
            LEX_ERROR();
        case 165:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(165);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(127);
            if (lookahead == ',')
                ADVANCE(134);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(99);
            LEX_ERROR();
        case 166:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(166);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '.')
                ADVANCE(167);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(114);
            if (lookahead == '{')
                ADVANCE(104);
            LEX_ERROR();
        case 167:
            ACCEPT_TOKEN(anon_sym_DOT);
        case 168:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(168);
            if (lookahead == ',')
                ADVANCE(134);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(109);
            LEX_ERROR();
        case 169:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(169);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(127);
            if (lookahead == ',')
                ADVANCE(134);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(109);
            LEX_ERROR();
        case 170:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(170);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(161);
            LEX_ERROR();
        case 171:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(171);
            if (lookahead == '.')
                ADVANCE(167);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(161);
            if (lookahead == '[')
                ADVANCE(114);
            LEX_ERROR();
        case 172:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(172);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '.')
                ADVANCE(167);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(114);
            if (lookahead == '{')
                ADVANCE(104);
            if (lookahead == '}')
                ADVANCE(109);
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
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(99);
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
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(99);
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
                ADVANCE(134);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(161);
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
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(99);
            LEX_ERROR();
        case 177:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(177);
            if (lookahead == '\n')
                ADVANCE(178);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '#')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(127);
            if (lookahead == ',')
                ADVANCE(134);
            if (lookahead == '.')
                ADVANCE(167);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            if (lookahead == ';')
                ADVANCE(99);
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
                ADVANCE(125);
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
                ADVANCE(104);
            if (lookahead == '}')
                ADVANCE(109);
            LEX_ERROR();
        case 178:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '#')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(127);
            if (lookahead == ',')
                ADVANCE(134);
            if (lookahead == '.')
                ADVANCE(167);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            if (lookahead == ';')
                ADVANCE(99);
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
                ADVANCE(125);
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
                ADVANCE(104);
            if (lookahead == '}')
                ADVANCE(109);
            ACCEPT_TOKEN(anon_sym_LF);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(177);
            if (lookahead == '\n')
                ADVANCE(178);
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '#')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(106);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(127);
            if (lookahead == ',')
                ADVANCE(134);
            if (lookahead == '.')
                ADVANCE(167);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(122);
            if (lookahead == ';')
                ADVANCE(99);
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
                ADVANCE(125);
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
                ADVANCE(104);
            if (lookahead == '}')
                ADVANCE(109);
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
    [9] = 100,
    [10] = 100,
    [11] = 95,
    [12] = 101,
    [13] = 103,
    [14] = 95,
    [15] = 96,
    [16] = 92,
    [17] = 105,
    [18] = 105,
    [19] = 100,
    [20] = 103,
    [21] = 107,
    [22] = 92,
    [23] = 105,
    [24] = 105,
    [25] = 108,
    [26] = 110,
    [27] = 108,
    [28] = 111,
    [29] = 111,
    [30] = 108,
    [31] = 100,
    [32] = 112,
    [33] = 103,
    [34] = 105,
    [35] = 111,
    [36] = 92,
    [37] = 105,
    [38] = 111,
    [39] = 108,
    [40] = 110,
    [41] = 108,
    [42] = 112,
    [43] = 111,
    [44] = 111,
    [45] = 112,
    [46] = 111,
    [47] = 105,
    [48] = 111,
    [49] = 112,
    [50] = 113,
    [51] = 113,
    [52] = 111,
    [53] = 111,
    [54] = 113,
    [55] = 115,
    [56] = 116,
    [57] = 126,
    [58] = 126,
    [59] = 128,
    [60] = 113,
    [61] = 131,
    [62] = 126,
    [63] = 132,
    [64] = 131,
    [65] = 131,
    [66] = 126,
    [67] = 126,
    [68] = 133,
    [69] = 133,
    [70] = 128,
    [71] = 126,
    [72] = 131,
    [73] = 133,
    [74] = 132,
    [75] = 131,
    [76] = 131,
    [77] = 133,
    [78] = 133,
    [79] = 133,
    [80] = 133,
    [81] = 105,
    [82] = 133,
    [83] = 131,
    [84] = 133,
    [85] = 105,
    [86] = 133,
    [87] = 135,
    [88] = 135,
    [89] = 105,
    [90] = 136,
    [91] = 137,
    [92] = 137,
    [93] = 100,
    [94] = 92,
    [95] = 128,
    [96] = 103,
    [97] = 131,
    [98] = 136,
    [99] = 137,
    [100] = 92,
    [101] = 105,
    [102] = 135,
    [103] = 137,
    [104] = 132,
    [105] = 131,
    [106] = 131,
    [107] = 137,
    [108] = 137,
    [109] = 133,
    [110] = 137,
    [111] = 105,
    [112] = 137,
    [113] = 137,
    [114] = 108,
    [115] = 110,
    [116] = 108,
    [117] = 112,
    [118] = 135,
    [119] = 135,
    [120] = 112,
    [121] = 135,
    [122] = 105,
    [123] = 137,
    [124] = 137,
    [125] = 131,
    [126] = 137,
    [127] = 135,
    [128] = 135,
    [129] = 138,
    [130] = 138,
    [131] = 139,
    [132] = 140,
    [133] = 138,
    [134] = 115,
    [135] = 116,
    [136] = 126,
    [137] = 138,
    [138] = 138,
    [139] = 92,
    [140] = 111,
    [141] = 141,
    [142] = 138,
    [143] = 105,
    [144] = 138,
    [145] = 95,
    [146] = 141,
    [147] = 105,
    [148] = 138,
    [149] = 142,
    [150] = 142,
    [151] = 111,
    [152] = 111,
    [153] = 142,
    [154] = 115,
    [155] = 116,
    [156] = 126,
    [157] = 142,
    [158] = 142,
    [159] = 141,
    [160] = 142,
    [161] = 105,
    [162] = 142,
    [163] = 142,
    [164] = 138,
    [165] = 138,
    [166] = 111,
    [167] = 111,
    [168] = 138,
    [169] = 115,
    [170] = 116,
    [171] = 126,
    [172] = 138,
    [173] = 138,
    [174] = 141,
    [175] = 138,
    [176] = 105,
    [177] = 138,
    [178] = 138,
    [179] = 138,
    [180] = 138,
    [181] = 142,
    [182] = 111,
    [183] = 142,
    [184] = 138,
    [185] = 138,
    [186] = 135,
    [187] = 133,
    [188] = 92,
    [189] = 131,
    [190] = 133,
    [191] = 138,
    [192] = 105,
    [193] = 126,
    [194] = 126,
    [195] = 105,
    [196] = 137,
    [197] = 126,
    [198] = 131,
    [199] = 126,
    [200] = 113,
    [201] = 141,
    [202] = 113,
    [203] = 105,
    [204] = 113,
    [205] = 113,
    [206] = 138,
    [207] = 113,
    [208] = 112,
    [209] = 105,
    [210] = 105,
    [211] = 96,
    [212] = 108,
    [213] = 110,
    [214] = 108,
    [215] = 112,
    [216] = 96,
    [217] = 96,
    [218] = 112,
    [219] = 96,
    [220] = 100,
    [221] = 143,
    [222] = 1,
    [223] = 157,
    [224] = 1,
    [225] = 96,
    [226] = 159,
    [227] = 160,
    [228] = 160,
    [229] = 111,
    [230] = 1,
    [231] = 111,
    [232] = 160,
    [233] = 115,
    [234] = 116,
    [235] = 126,
    [236] = 160,
    [237] = 160,
    [238] = 141,
    [239] = 160,
    [240] = 105,
    [241] = 160,
    [242] = 160,
    [243] = 138,
    [244] = 160,
    [245] = 92,
    [246] = 96,
    [247] = 162,
    [248] = 1,
    [249] = 110,
    [250] = 163,
    [251] = 164,
    [252] = 159,
    [253] = 165,
    [254] = 165,
    [255] = 128,
    [256] = 166,
    [257] = 131,
    [258] = 165,
    [259] = 132,
    [260] = 131,
    [261] = 131,
    [262] = 165,
    [263] = 165,
    [264] = 133,
    [265] = 165,
    [266] = 105,
    [267] = 165,
    [268] = 165,
    [269] = 168,
    [270] = 168,
    [271] = 164,
    [272] = 169,
    [273] = 169,
    [274] = 170,
    [275] = 128,
    [276] = 166,
    [277] = 131,
    [278] = 100,
    [279] = 131,
    [280] = 169,
    [281] = 132,
    [282] = 131,
    [283] = 131,
    [284] = 169,
    [285] = 169,
    [286] = 133,
    [287] = 169,
    [288] = 105,
    [289] = 169,
    [290] = 169,
    [291] = 171,
    [292] = 170,
    [293] = 126,
    [294] = 171,
    [295] = 170,
    [296] = 168,
    [297] = 168,
    [298] = 172,
    [299] = 168,
    [300] = 164,
    [301] = 168,
    [302] = 168,
    [303] = 105,
    [304] = 137,
    [305] = 169,
    [306] = 131,
    [307] = 169,
    [308] = 164,
    [309] = 168,
    [310] = 159,
    [311] = 172,
    [312] = 159,
    [313] = 105,
    [314] = 137,
    [315] = 165,
    [316] = 131,
    [317] = 165,
    [318] = 92,
    [319] = 96,
    [320] = 163,
    [321] = 173,
    [322] = 173,
    [323] = 163,
    [324] = 112,
    [325] = 128,
    [326] = 1,
    [327] = 131,
    [328] = 174,
    [329] = 173,
    [330] = 132,
    [331] = 131,
    [332] = 131,
    [333] = 173,
    [334] = 173,
    [335] = 133,
    [336] = 173,
    [337] = 105,
    [338] = 173,
    [339] = 173,
    [340] = 105,
    [341] = 137,
    [342] = 173,
    [343] = 131,
    [344] = 173,
    [345] = 1,
    [346] = 163,
    [347] = 112,
    [348] = 159,
    [349] = 175,
    [350] = 175,
    [351] = 111,
    [352] = 163,
    [353] = 111,
    [354] = 175,
    [355] = 115,
    [356] = 116,
    [357] = 126,
    [358] = 175,
    [359] = 175,
    [360] = 141,
    [361] = 175,
    [362] = 105,
    [363] = 175,
    [364] = 175,
    [365] = 138,
    [366] = 175,
    [367] = 176,
    [368] = 111,
    [369] = 163,
    [370] = 159,
    [371] = 176,
    [372] = 163,
    [373] = 96,
    [374] = 159,
    [375] = 176,
    [376] = 163,
    [377] = 1,
    [378] = 110,
    [379] = 159,
    [380] = 162,
    [381] = 176,
    [382] = 162,
    [383] = 162,
    [384] = 96,
    [385] = 159,
    [386] = 176,
    [387] = 162,
    [388] = 176,
    [389] = 1,
    [390] = 1,
    [391] = 92,
    [392] = 96,
    [393] = 159,
    [394] = 160,
    [395] = 110,
    [396] = 1,
    [397] = 176,
    [398] = 1,
    [399] = 91,
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
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(2)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_translation_unit, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(SHIFT(10)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
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
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(2)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(399)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 1)),
        [anon_sym_POUNDdefine] = ACTIONS(SHIFT(10)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [3] = {
        [sym__type_specifier] = ACTIONS(SHIFT(392)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [4] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(391)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [5] = {
        [sym__init_declarator] = ACTIONS(SHIFT(226)),
        [sym__declarator] = ACTIONS(SHIFT(227)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(228)),
        [sym_function_declarator] = ACTIONS(SHIFT(228)),
        [sym_array_declarator] = ACTIONS(SHIFT(228)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(229)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(230)),
        [anon_sym_STAR] = ACTIONS(SHIFT(231)),
        [sym_identifier] = ACTIONS(SHIFT(228)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__type_specifier, 1)),
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
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
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
        [sym_identifier] = ACTIONS(SHIFT(225)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [sym_identifier] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
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
    [12] = {
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(220)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_numeric_type_specifier_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(212)),
        [sym_identifier] = ACTIONS(SHIFT(213)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
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
    [15] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), SHIFT(16)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym__type_specifier] = ACTIONS(SHIFT(17)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(18)),
        [sym_macro_type] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(19)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(20)),
        [sym_identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [sym_identifier] = ACTIONS(SHIFT(210)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(25)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(22)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [sym__type_specifier] = ACTIONS(SHIFT(23)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(18)),
        [sym_macro_type] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(19)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(20)),
        [sym_identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [sym__type_specifier] = ACTIONS(SHIFT(28)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_struct_declaration] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(208)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(209)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [sym__type_specifier] = ACTIONS(SHIFT(28)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_struct_declaration] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [sym__declarator] = ACTIONS(SHIFT(50)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(51)),
        [sym_function_declarator] = ACTIONS(SHIFT(51)),
        [sym_array_declarator] = ACTIONS(SHIFT(51)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(52)),
        [anon_sym_STAR] = ACTIONS(SHIFT(53)),
        [sym_identifier] = ACTIONS(SHIFT(51)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [sym__type_specifier] = ACTIONS(SHIFT(28)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_struct_declaration] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(49)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [sym_identifier] = ACTIONS(SHIFT(48)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(47)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [33] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(39)),
        [sym_identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [34] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [35] = {
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), SHIFT(36)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [36] = {
        [sym__type_specifier] = ACTIONS(SHIFT(37)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(18)),
        [sym_macro_type] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(19)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(20)),
        [sym_identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [37] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(38)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [38] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [39] = {
        [sym__type_specifier] = ACTIONS(SHIFT(28)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_struct_declaration] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(45)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(46)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [40] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [41] = {
        [sym__type_specifier] = ACTIONS(SHIFT(28)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_struct_declaration] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(42)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [42] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(44)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [43] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [44] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [45] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [46] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [47] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [48] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [49] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [50] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(55)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(56)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [51] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__declarator, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [52] = {
        [sym__declarator] = ACTIONS(SHIFT(206)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(165)),
        [sym_function_declarator] = ACTIONS(SHIFT(165)),
        [sym_array_declarator] = ACTIONS(SHIFT(165)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(166)),
        [anon_sym_STAR] = ACTIONS(SHIFT(167)),
        [sym_identifier] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [53] = {
        [sym__declarator] = ACTIONS(SHIFT(54)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(51)),
        [sym_function_declarator] = ACTIONS(SHIFT(51)),
        [sym_array_declarator] = ACTIONS(SHIFT(51)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(52)),
        [anon_sym_STAR] = ACTIONS(SHIFT(53)),
        [sym_identifier] = ACTIONS(SHIFT(51)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [54] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(55)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(56)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [55] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(139)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(140)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(201)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(202)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [56] = {
        [sym__expression] = ACTIONS(SHIFT(57)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(60)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [57] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(200)),
        [anon_sym_STAR] = ACTIONS(SHIFT(64)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [58] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [59] = {
        [sym__type_specifier] = ACTIONS(SHIFT(87)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(88)),
        [sym_macro_type] = ACTIONS(SHIFT(88)),
        [sym_struct_specifier] = ACTIONS(SHIFT(88)),
        [sym_type_name] = ACTIONS(SHIFT(195)),
        [sym_type_qualifier] = ACTIONS(SHIFT(90)),
        [sym__expression] = ACTIONS(SHIFT(196)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(93)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(94)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_struct] = ACTIONS(SHIFT(96)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_const] = ACTIONS(SHIFT(98)),
        [anon_sym_restrict] = ACTIONS(SHIFT(98)),
        [anon_sym_volatile] = ACTIONS(SHIFT(98)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(99)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [60] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [61] = {
        [sym__expression] = ACTIONS(SHIFT(62)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [62] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(64)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [63] = {
        [sym__expression] = ACTIONS(SHIFT(68)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(71)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [64] = {
        [sym__expression] = ACTIONS(SHIFT(67)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [65] = {
        [sym__expression] = ACTIONS(SHIFT(66)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [66] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(64)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [67] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [68] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(192)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(193)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(75)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [69] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [70] = {
        [sym__type_specifier] = ACTIONS(SHIFT(87)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(88)),
        [sym_macro_type] = ACTIONS(SHIFT(88)),
        [sym_struct_specifier] = ACTIONS(SHIFT(88)),
        [sym_type_name] = ACTIONS(SHIFT(89)),
        [sym_type_qualifier] = ACTIONS(SHIFT(90)),
        [sym__expression] = ACTIONS(SHIFT(91)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(93)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(94)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_struct] = ACTIONS(SHIFT(96)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_const] = ACTIONS(SHIFT(98)),
        [anon_sym_restrict] = ACTIONS(SHIFT(98)),
        [anon_sym_volatile] = ACTIONS(SHIFT(98)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(99)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [71] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [72] = {
        [sym__expression] = ACTIONS(SHIFT(73)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(75)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [sym__expression] = ACTIONS(SHIFT(79)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [75] = {
        [sym__expression] = ACTIONS(SHIFT(78)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [sym__expression] = ACTIONS(SHIFT(77)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(75)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(82)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(75)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [80] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [82] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [sym__expression] = ACTIONS(SHIFT(84)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(85)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(75)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(191)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(130)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(130)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(130)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(131)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(132)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(189)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(90)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(188)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(98)),
        [anon_sym_restrict] = ACTIONS(SHIFT(98)),
        [anon_sym_volatile] = ACTIONS(SHIFT(98)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(187)),
        [anon_sym_STAR] = ACTIONS(SHIFT(105)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(106)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [sym_identifier] = ACTIONS(SHIFT(186)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [sym__type_specifier] = ACTIONS(SHIFT(127)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(88)),
        [sym_macro_type] = ACTIONS(SHIFT(88)),
        [sym_struct_specifier] = ACTIONS(SHIFT(88)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(93)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(96)),
        [sym_identifier] = ACTIONS(SHIFT(128)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [sym__type_specifier] = ACTIONS(SHIFT(87)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(88)),
        [sym_macro_type] = ACTIONS(SHIFT(88)),
        [sym_struct_specifier] = ACTIONS(SHIFT(88)),
        [sym_type_name] = ACTIONS(SHIFT(122)),
        [sym_type_qualifier] = ACTIONS(SHIFT(90)),
        [sym__expression] = ACTIONS(SHIFT(123)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(93)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(94)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_struct] = ACTIONS(SHIFT(96)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_const] = ACTIONS(SHIFT(98)),
        [anon_sym_restrict] = ACTIONS(SHIFT(98)),
        [anon_sym_volatile] = ACTIONS(SHIFT(98)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(99)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(114)),
        [sym_identifier] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [sym__expression] = ACTIONS(SHIFT(103)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
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
    [99] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1), SHIFT(100)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [sym__type_specifier] = ACTIONS(SHIFT(101)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(18)),
        [sym_macro_type] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(19)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(20)),
        [sym_identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(102)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [103] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(105)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(106)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [sym__expression] = ACTIONS(SHIFT(109)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(110)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
        [sym__expression] = ACTIONS(SHIFT(108)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [106] = {
        [sym__expression] = ACTIONS(SHIFT(107)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [107] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(105)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [108] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(111)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(112)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(75)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(113)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [sym__type_specifier] = ACTIONS(SHIFT(28)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_struct_declaration] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(120)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(121)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(116)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [116] = {
        [sym__type_specifier] = ACTIONS(SHIFT(28)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_struct_declaration] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(117)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(118)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [117] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [119] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [120] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(118)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [121] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [122] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [123] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(124)),
        [anon_sym_STAR] = ACTIONS(SHIFT(105)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(106)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [124] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [125] = {
        [sym__expression] = ACTIONS(SHIFT(126)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(129)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(130)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(130)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(130)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(131)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(132)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), SHIFT(100)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(134)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 3)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__abstract_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [131] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(184)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(130)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(130)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(130)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(131)),
        [anon_sym_STAR] = ACTIONS(SHIFT(132)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(133)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(130)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(130)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(130)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(131)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_pointer_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_pointer_declarator, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(132)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [133] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(134)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(139)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(140)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(141)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(142)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [sym__expression] = ACTIONS(SHIFT(136)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(137)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(138)),
        [anon_sym_STAR] = ACTIONS(SHIFT(64)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [139] = {
        [sym__type_specifier] = ACTIONS(SHIFT(182)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [140] = {
        [sym__declarator] = ACTIONS(SHIFT(149)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(150)),
        [sym_function_declarator] = ACTIONS(SHIFT(150)),
        [sym_array_declarator] = ACTIONS(SHIFT(150)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(151)),
        [anon_sym_STAR] = ACTIONS(SHIFT(152)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(143)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(144)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(145)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(148)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [144] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [145] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(139)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(140)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(146)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(147)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_function_declarator_repeat1, 2)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(145)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_function_declarator_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(154)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(155)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [sym__declarator] = ACTIONS(SHIFT(164)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(165)),
        [sym_function_declarator] = ACTIONS(SHIFT(165)),
        [sym_array_declarator] = ACTIONS(SHIFT(165)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(166)),
        [anon_sym_STAR] = ACTIONS(SHIFT(167)),
        [sym_identifier] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [sym__declarator] = ACTIONS(SHIFT(153)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(150)),
        [sym_function_declarator] = ACTIONS(SHIFT(150)),
        [sym_array_declarator] = ACTIONS(SHIFT(150)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(151)),
        [anon_sym_STAR] = ACTIONS(SHIFT(152)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(154)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(155)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(139)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(140)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(159)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(160)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [sym__expression] = ACTIONS(SHIFT(156)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(157)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(158)),
        [anon_sym_STAR] = ACTIONS(SHIFT(64)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(161)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(162)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(145)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(163)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(181)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [sym__declarator] = ACTIONS(SHIFT(179)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(165)),
        [sym_function_declarator] = ACTIONS(SHIFT(165)),
        [sym_array_declarator] = ACTIONS(SHIFT(165)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(166)),
        [anon_sym_STAR] = ACTIONS(SHIFT(167)),
        [sym_identifier] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [sym__declarator] = ACTIONS(SHIFT(168)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(165)),
        [sym_function_declarator] = ACTIONS(SHIFT(165)),
        [sym_array_declarator] = ACTIONS(SHIFT(165)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(166)),
        [anon_sym_STAR] = ACTIONS(SHIFT(167)),
        [sym_identifier] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(139)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(140)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(174)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(175)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [sym__expression] = ACTIONS(SHIFT(171)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(172)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(173)),
        [anon_sym_STAR] = ACTIONS(SHIFT(64)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [172] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(176)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(177)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(145)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(178)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(180)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [180] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [sym__declarator] = ACTIONS(SHIFT(183)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(150)),
        [sym_function_declarator] = ACTIONS(SHIFT(150)),
        [sym_array_declarator] = ACTIONS(SHIFT(150)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(151)),
        [anon_sym_STAR] = ACTIONS(SHIFT(152)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(154)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(155)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(134)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(185)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [185] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__abstract_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [186] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [188] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [sym__expression] = ACTIONS(SHIFT(190)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(134)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(198)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(197)),
        [anon_sym_STAR] = ACTIONS(SHIFT(105)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(106)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [sym__expression] = ACTIONS(SHIFT(199)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(203)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(204)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(145)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(205)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(207)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__declarator, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(34)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [209] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym__declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
        [sym__type_specifier] = ACTIONS(SHIFT(28)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_struct_declaration] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(218)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(219)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [213] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(214)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [sym__type_specifier] = ACTIONS(SHIFT(28)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_struct_declaration] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(215)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(216)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(217)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [219] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_numeric_type_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [anon_sym_LF] = ACTIONS(SHIFT(222)),
        [sym_preproc_arg] = ACTIONS(SHIFT(223)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3)),
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
    [223] = {
        [anon_sym_LF] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4)),
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
    [225] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym__declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(388)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(368)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(389)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(245)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(246)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(247)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(248)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(249)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(233)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(250)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(251)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(234)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [228] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__declarator, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [sym__declarator] = ACTIONS(SHIFT(243)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(165)),
        [sym_function_declarator] = ACTIONS(SHIFT(165)),
        [sym_array_declarator] = ACTIONS(SHIFT(165)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(166)),
        [anon_sym_STAR] = ACTIONS(SHIFT(167)),
        [sym_identifier] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
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
    [231] = {
        [sym__declarator] = ACTIONS(SHIFT(232)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(228)),
        [sym_function_declarator] = ACTIONS(SHIFT(228)),
        [sym_array_declarator] = ACTIONS(SHIFT(228)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(229)),
        [anon_sym_STAR] = ACTIONS(SHIFT(231)),
        [sym_identifier] = ACTIONS(SHIFT(228)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(233)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(234)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [233] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(139)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(140)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(238)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(239)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [sym__expression] = ACTIONS(SHIFT(235)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(236)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(237)),
        [anon_sym_STAR] = ACTIONS(SHIFT(64)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [237] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [238] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(240)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(241)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(145)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [240] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(242)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [241] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [243] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(244)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__declarator, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
        [sym__type_specifier] = ACTIONS(SHIFT(384)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [246] = {
        [sym__init_declarator] = ACTIONS(SHIFT(379)),
        [sym__declarator] = ACTIONS(SHIFT(349)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(380)),
        [anon_sym_STAR] = ACTIONS(SHIFT(353)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [247] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(245)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(246)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(247)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(378)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
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
    [249] = {
        [sym_compound_statement] = ACTIONS(SHIFT(377)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(250)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [250] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(318)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(319)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(320)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym__expression] = ACTIONS(SHIFT(321)),
        [sym_cast_expression] = ACTIONS(SHIFT(322)),
        [sym_math_expression] = ACTIONS(SHIFT(322)),
        [sym_call_expression] = ACTIONS(SHIFT(322)),
        [sym_pointer_expression] = ACTIONS(SHIFT(322)),
        [sym__statement] = ACTIONS(SHIFT(320)),
        [sym_expression_statement] = ACTIONS(SHIFT(323)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(324)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(324)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(325)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(326)),
        [anon_sym_STAR] = ACTIONS(SHIFT(327)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [anon_sym_AMP] = ACTIONS(SHIFT(327)),
        [sym_string] = ACTIONS(SHIFT(322)),
        [sym_identifier] = ACTIONS(SHIFT(328)),
        [sym_number] = ACTIONS(SHIFT(322)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [sym_initializer] = ACTIONS(SHIFT(252)),
        [sym__expression] = ACTIONS(SHIFT(253)),
        [sym_cast_expression] = ACTIONS(SHIFT(254)),
        [sym_math_expression] = ACTIONS(SHIFT(254)),
        [sym_call_expression] = ACTIONS(SHIFT(254)),
        [sym_pointer_expression] = ACTIONS(SHIFT(254)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(255)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(256)),
        [anon_sym_STAR] = ACTIONS(SHIFT(257)),
        [anon_sym_AMP] = ACTIONS(SHIFT(257)),
        [sym_string] = ACTIONS(SHIFT(254)),
        [sym_identifier] = ACTIONS(SHIFT(254)),
        [sym_number] = ACTIONS(SHIFT(254)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(259)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(260)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(261)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
        [sym__type_specifier] = ACTIONS(SHIFT(87)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(88)),
        [sym_macro_type] = ACTIONS(SHIFT(88)),
        [sym_struct_specifier] = ACTIONS(SHIFT(88)),
        [sym_type_name] = ACTIONS(SHIFT(313)),
        [sym_type_qualifier] = ACTIONS(SHIFT(90)),
        [sym__expression] = ACTIONS(SHIFT(314)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(93)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(94)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_struct] = ACTIONS(SHIFT(96)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_const] = ACTIONS(SHIFT(98)),
        [anon_sym_restrict] = ACTIONS(SHIFT(98)),
        [anon_sym_volatile] = ACTIONS(SHIFT(98)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(99)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [sym_initializer] = ACTIONS(SHIFT(269)),
        [sym_initializer_list] = ACTIONS(SHIFT(270)),
        [sym_designation] = ACTIONS(SHIFT(271)),
        [sym__expression] = ACTIONS(SHIFT(272)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(274)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(276)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(277)),
        [anon_sym_DOT] = ACTIONS(SHIFT(278)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [sym__expression] = ACTIONS(SHIFT(258)),
        [sym_cast_expression] = ACTIONS(SHIFT(254)),
        [sym_math_expression] = ACTIONS(SHIFT(254)),
        [sym_call_expression] = ACTIONS(SHIFT(254)),
        [sym_pointer_expression] = ACTIONS(SHIFT(254)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(255)),
        [anon_sym_STAR] = ACTIONS(SHIFT(257)),
        [anon_sym_AMP] = ACTIONS(SHIFT(257)),
        [sym_string] = ACTIONS(SHIFT(254)),
        [sym_identifier] = ACTIONS(SHIFT(254)),
        [sym_number] = ACTIONS(SHIFT(254)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(259)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(260)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(261)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [259] = {
        [sym__expression] = ACTIONS(SHIFT(264)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(265)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [260] = {
        [sym__expression] = ACTIONS(SHIFT(263)),
        [sym_cast_expression] = ACTIONS(SHIFT(254)),
        [sym_math_expression] = ACTIONS(SHIFT(254)),
        [sym_call_expression] = ACTIONS(SHIFT(254)),
        [sym_pointer_expression] = ACTIONS(SHIFT(254)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(255)),
        [anon_sym_STAR] = ACTIONS(SHIFT(257)),
        [anon_sym_AMP] = ACTIONS(SHIFT(257)),
        [sym_string] = ACTIONS(SHIFT(254)),
        [sym_identifier] = ACTIONS(SHIFT(254)),
        [sym_number] = ACTIONS(SHIFT(254)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [261] = {
        [sym__expression] = ACTIONS(SHIFT(262)),
        [sym_cast_expression] = ACTIONS(SHIFT(254)),
        [sym_math_expression] = ACTIONS(SHIFT(254)),
        [sym_call_expression] = ACTIONS(SHIFT(254)),
        [sym_pointer_expression] = ACTIONS(SHIFT(254)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(255)),
        [anon_sym_STAR] = ACTIONS(SHIFT(257)),
        [anon_sym_AMP] = ACTIONS(SHIFT(257)),
        [sym_string] = ACTIONS(SHIFT(254)),
        [sym_identifier] = ACTIONS(SHIFT(254)),
        [sym_number] = ACTIONS(SHIFT(254)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [262] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(259)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(260)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(259)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [264] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(266)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(267)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(75)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [265] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(268)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [267] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [268] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [269] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [270] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(310)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(311)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [271] = {
        [sym_initializer] = ACTIONS(SHIFT(309)),
        [sym__expression] = ACTIONS(SHIFT(272)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(276)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [272] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(281)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(282)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(283)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [273] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [274] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(308)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [275] = {
        [sym__type_specifier] = ACTIONS(SHIFT(87)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(88)),
        [sym_macro_type] = ACTIONS(SHIFT(88)),
        [sym_struct_specifier] = ACTIONS(SHIFT(88)),
        [sym_type_name] = ACTIONS(SHIFT(303)),
        [sym_type_qualifier] = ACTIONS(SHIFT(90)),
        [sym__expression] = ACTIONS(SHIFT(304)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(93)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(94)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_struct] = ACTIONS(SHIFT(96)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_const] = ACTIONS(SHIFT(98)),
        [anon_sym_restrict] = ACTIONS(SHIFT(98)),
        [anon_sym_volatile] = ACTIONS(SHIFT(98)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(99)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [276] = {
        [sym_initializer] = ACTIONS(SHIFT(269)),
        [sym_initializer_list] = ACTIONS(SHIFT(296)),
        [sym_designation] = ACTIONS(SHIFT(271)),
        [sym__expression] = ACTIONS(SHIFT(272)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(274)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(276)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(277)),
        [anon_sym_DOT] = ACTIONS(SHIFT(278)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [277] = {
        [sym__expression] = ACTIONS(SHIFT(293)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [278] = {
        [sym_identifier] = ACTIONS(SHIFT(291)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [279] = {
        [sym__expression] = ACTIONS(SHIFT(280)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [280] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(281)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(282)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(283)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [281] = {
        [sym__expression] = ACTIONS(SHIFT(286)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(287)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [282] = {
        [sym__expression] = ACTIONS(SHIFT(285)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [283] = {
        [sym__expression] = ACTIONS(SHIFT(284)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [284] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(281)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(282)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [285] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(281)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [286] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(288)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(289)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(75)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [287] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [288] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [289] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [290] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [291] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(292)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(277)),
        [anon_sym_DOT] = ACTIONS(SHIFT(278)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [292] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [293] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(294)),
        [anon_sym_STAR] = ACTIONS(SHIFT(64)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [294] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(295)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(277)),
        [anon_sym_DOT] = ACTIONS(SHIFT(278)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [295] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [296] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(297)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(298)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [297] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [298] = {
        [sym_initializer] = ACTIONS(SHIFT(299)),
        [sym_designation] = ACTIONS(SHIFT(300)),
        [sym__expression] = ACTIONS(SHIFT(272)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(274)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(276)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(301)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(277)),
        [anon_sym_DOT] = ACTIONS(SHIFT(278)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [299] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [300] = {
        [sym_initializer] = ACTIONS(SHIFT(302)),
        [sym__expression] = ACTIONS(SHIFT(272)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(276)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [301] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [302] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [303] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(306)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [304] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(305)),
        [anon_sym_STAR] = ACTIONS(SHIFT(105)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(106)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [305] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [306] = {
        [sym__expression] = ACTIONS(SHIFT(307)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [307] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [308] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [309] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [310] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [311] = {
        [sym_initializer] = ACTIONS(SHIFT(299)),
        [sym_designation] = ACTIONS(SHIFT(300)),
        [sym__expression] = ACTIONS(SHIFT(272)),
        [sym_cast_expression] = ACTIONS(SHIFT(273)),
        [sym_math_expression] = ACTIONS(SHIFT(273)),
        [sym_call_expression] = ACTIONS(SHIFT(273)),
        [sym_pointer_expression] = ACTIONS(SHIFT(273)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(274)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(276)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(312)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(277)),
        [anon_sym_DOT] = ACTIONS(SHIFT(278)),
        [anon_sym_STAR] = ACTIONS(SHIFT(279)),
        [anon_sym_AMP] = ACTIONS(SHIFT(279)),
        [sym_string] = ACTIONS(SHIFT(273)),
        [sym_identifier] = ACTIONS(SHIFT(273)),
        [sym_number] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [312] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [313] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(316)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [314] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(315)),
        [anon_sym_STAR] = ACTIONS(SHIFT(105)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(106)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [315] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [316] = {
        [sym__expression] = ACTIONS(SHIFT(317)),
        [sym_cast_expression] = ACTIONS(SHIFT(254)),
        [sym_math_expression] = ACTIONS(SHIFT(254)),
        [sym_call_expression] = ACTIONS(SHIFT(254)),
        [sym_pointer_expression] = ACTIONS(SHIFT(254)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(255)),
        [anon_sym_STAR] = ACTIONS(SHIFT(257)),
        [anon_sym_AMP] = ACTIONS(SHIFT(257)),
        [sym_string] = ACTIONS(SHIFT(254)),
        [sym_identifier] = ACTIONS(SHIFT(254)),
        [sym_number] = ACTIONS(SHIFT(254)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [317] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [318] = {
        [sym__type_specifier] = ACTIONS(SHIFT(373)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [319] = {
        [sym__init_declarator] = ACTIONS(SHIFT(348)),
        [sym__declarator] = ACTIONS(SHIFT(349)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(352)),
        [anon_sym_STAR] = ACTIONS(SHIFT(353)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [320] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(318)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(319)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(320)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym__expression] = ACTIONS(SHIFT(321)),
        [sym_cast_expression] = ACTIONS(SHIFT(322)),
        [sym_math_expression] = ACTIONS(SHIFT(322)),
        [sym_call_expression] = ACTIONS(SHIFT(322)),
        [sym_pointer_expression] = ACTIONS(SHIFT(322)),
        [sym__statement] = ACTIONS(SHIFT(320)),
        [sym_expression_statement] = ACTIONS(SHIFT(323)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(347)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(325)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(327)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [anon_sym_AMP] = ACTIONS(SHIFT(327)),
        [sym_string] = ACTIONS(SHIFT(322)),
        [sym_identifier] = ACTIONS(SHIFT(328)),
        [sym_number] = ACTIONS(SHIFT(322)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [321] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(330)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(346)),
        [anon_sym_STAR] = ACTIONS(SHIFT(331)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(332)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [322] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [323] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__statement, 1)),
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
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__statement, 1)),
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
    [324] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(345)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [325] = {
        [sym__type_specifier] = ACTIONS(SHIFT(87)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(88)),
        [sym_macro_type] = ACTIONS(SHIFT(88)),
        [sym_struct_specifier] = ACTIONS(SHIFT(88)),
        [sym_type_name] = ACTIONS(SHIFT(340)),
        [sym_type_qualifier] = ACTIONS(SHIFT(90)),
        [sym__expression] = ACTIONS(SHIFT(341)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(93)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(94)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_struct] = ACTIONS(SHIFT(96)),
        [anon_sym_STAR] = ACTIONS(SHIFT(97)),
        [anon_sym_const] = ACTIONS(SHIFT(98)),
        [anon_sym_restrict] = ACTIONS(SHIFT(98)),
        [anon_sym_volatile] = ACTIONS(SHIFT(98)),
        [anon_sym_AMP] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(99)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [326] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
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
    [327] = {
        [sym__expression] = ACTIONS(SHIFT(329)),
        [sym_cast_expression] = ACTIONS(SHIFT(322)),
        [sym_math_expression] = ACTIONS(SHIFT(322)),
        [sym_call_expression] = ACTIONS(SHIFT(322)),
        [sym_pointer_expression] = ACTIONS(SHIFT(322)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(325)),
        [anon_sym_STAR] = ACTIONS(SHIFT(327)),
        [anon_sym_AMP] = ACTIONS(SHIFT(327)),
        [sym_string] = ACTIONS(SHIFT(322)),
        [sym_identifier] = ACTIONS(SHIFT(322)),
        [sym_number] = ACTIONS(SHIFT(322)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [328] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1), SHIFT(16)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [329] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(330)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(331)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(332)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [330] = {
        [sym__expression] = ACTIONS(SHIFT(335)),
        [sym_cast_expression] = ACTIONS(SHIFT(69)),
        [sym_math_expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(69)),
        [sym_pointer_expression] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(336)),
        [anon_sym_STAR] = ACTIONS(SHIFT(72)),
        [anon_sym_AMP] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(69)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_number] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [331] = {
        [sym__expression] = ACTIONS(SHIFT(334)),
        [sym_cast_expression] = ACTIONS(SHIFT(322)),
        [sym_math_expression] = ACTIONS(SHIFT(322)),
        [sym_call_expression] = ACTIONS(SHIFT(322)),
        [sym_pointer_expression] = ACTIONS(SHIFT(322)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(325)),
        [anon_sym_STAR] = ACTIONS(SHIFT(327)),
        [anon_sym_AMP] = ACTIONS(SHIFT(327)),
        [sym_string] = ACTIONS(SHIFT(322)),
        [sym_identifier] = ACTIONS(SHIFT(322)),
        [sym_number] = ACTIONS(SHIFT(322)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [332] = {
        [sym__expression] = ACTIONS(SHIFT(333)),
        [sym_cast_expression] = ACTIONS(SHIFT(322)),
        [sym_math_expression] = ACTIONS(SHIFT(322)),
        [sym_call_expression] = ACTIONS(SHIFT(322)),
        [sym_pointer_expression] = ACTIONS(SHIFT(322)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(325)),
        [anon_sym_STAR] = ACTIONS(SHIFT(327)),
        [anon_sym_AMP] = ACTIONS(SHIFT(327)),
        [sym_string] = ACTIONS(SHIFT(322)),
        [sym_identifier] = ACTIONS(SHIFT(322)),
        [sym_number] = ACTIONS(SHIFT(322)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [333] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(330)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(331)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [334] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(330)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [335] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(337)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(338)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(75)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [336] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [337] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(339)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [338] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [339] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [340] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(343)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [341] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(342)),
        [anon_sym_STAR] = ACTIONS(SHIFT(105)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(106)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [342] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [343] = {
        [sym__expression] = ACTIONS(SHIFT(344)),
        [sym_cast_expression] = ACTIONS(SHIFT(322)),
        [sym_math_expression] = ACTIONS(SHIFT(322)),
        [sym_call_expression] = ACTIONS(SHIFT(322)),
        [sym_pointer_expression] = ACTIONS(SHIFT(322)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(325)),
        [anon_sym_STAR] = ACTIONS(SHIFT(327)),
        [anon_sym_AMP] = ACTIONS(SHIFT(327)),
        [sym_string] = ACTIONS(SHIFT(322)),
        [sym_identifier] = ACTIONS(SHIFT(322)),
        [sym_number] = ACTIONS(SHIFT(322)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [344] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [345] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
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
    [346] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_expression_statement, 2)),
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
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
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
    [347] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [348] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(367)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(368)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(369)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [349] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(355)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(251)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(356)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [350] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [351] = {
        [sym__declarator] = ACTIONS(SHIFT(365)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(165)),
        [sym_function_declarator] = ACTIONS(SHIFT(165)),
        [sym_array_declarator] = ACTIONS(SHIFT(165)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(166)),
        [anon_sym_STAR] = ACTIONS(SHIFT(167)),
        [sym_identifier] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [352] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 2)),
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
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 2)),
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
    [353] = {
        [sym__declarator] = ACTIONS(SHIFT(354)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_STAR] = ACTIONS(SHIFT(353)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [354] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(355)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(356)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [355] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(139)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(140)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(29)),
        [sym_macro_type] = ACTIONS(SHIFT(29)),
        [sym_struct_specifier] = ACTIONS(SHIFT(29)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(360)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(361)),
        [anon_sym_struct] = ACTIONS(SHIFT(33)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [356] = {
        [sym__expression] = ACTIONS(SHIFT(357)),
        [sym_cast_expression] = ACTIONS(SHIFT(58)),
        [sym_math_expression] = ACTIONS(SHIFT(58)),
        [sym_call_expression] = ACTIONS(SHIFT(58)),
        [sym_pointer_expression] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(59)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(358)),
        [anon_sym_STAR] = ACTIONS(SHIFT(61)),
        [anon_sym_AMP] = ACTIONS(SHIFT(61)),
        [sym_string] = ACTIONS(SHIFT(58)),
        [sym_identifier] = ACTIONS(SHIFT(58)),
        [sym_number] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [357] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(63)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(359)),
        [anon_sym_STAR] = ACTIONS(SHIFT(64)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [358] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [359] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [360] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(362)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(363)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(145)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [361] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [362] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(364)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [363] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [364] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [365] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(366)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [366] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [367] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(372)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [368] = {
        [sym__init_declarator] = ACTIONS(SHIFT(370)),
        [sym__declarator] = ACTIONS(SHIFT(349)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_STAR] = ACTIONS(SHIFT(353)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [369] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 3)),
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
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 3)),
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
    [370] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(371)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(368)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [371] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [372] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 4)),
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
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 4)),
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
    [373] = {
        [sym__init_declarator] = ACTIONS(SHIFT(374)),
        [sym__declarator] = ACTIONS(SHIFT(349)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(369)),
        [anon_sym_STAR] = ACTIONS(SHIFT(353)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [374] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(375)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(368)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(372)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [375] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(376)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [376] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 5)),
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
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 5)),
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
    [377] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
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
    [378] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [379] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(381)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(368)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(382)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [380] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
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
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [381] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(383)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [382] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
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
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [383] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
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
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [384] = {
        [sym__init_declarator] = ACTIONS(SHIFT(385)),
        [sym__declarator] = ACTIONS(SHIFT(349)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(382)),
        [anon_sym_STAR] = ACTIONS(SHIFT(353)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [385] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(386)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(368)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(383)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [386] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(387)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [387] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
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
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [388] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(390)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [389] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
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
    [390] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
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
    [391] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [392] = {
        [sym__init_declarator] = ACTIONS(SHIFT(393)),
        [sym__declarator] = ACTIONS(SHIFT(394)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(228)),
        [sym_function_declarator] = ACTIONS(SHIFT(228)),
        [sym_array_declarator] = ACTIONS(SHIFT(228)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(229)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(389)),
        [anon_sym_STAR] = ACTIONS(SHIFT(231)),
        [sym_identifier] = ACTIONS(SHIFT(228)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [393] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(397)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(368)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(390)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [394] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(245)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(246)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(247)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(377)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(395)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(233)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(250)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(251)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(234)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [395] = {
        [sym_compound_statement] = ACTIONS(SHIFT(396)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(250)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [396] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [397] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(398)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [398] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
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
    [399] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
