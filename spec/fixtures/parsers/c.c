#include "tree_sitter/parser.h"

#define STATE_COUNT 261
#define SYMBOL_COUNT 65

enum {
    sym_program = ts_builtin_sym_start,
    sym_function_definition,
    sym_declaration_specifiers,
    sym_storage_class_specifier,
    sym__type_specifier,
    sym_type_name,
    sym_struct_specifier,
    sym_struct_declaration,
    sym_parameter_declaration,
    sym_declaration,
    sym__init_declarator,
    sym_initializer,
    sym_initializer_list,
    sym_designation,
    sym_declarator,
    sym__direct_declarator,
    sym_type_qualifier,
    sym_pointer,
    sym_compound_statement,
    sym_expression,
    sym_math_expression,
    sym_call_expression,
    sym_statement,
    sym_expression_statement,
    aux_sym_function_definition_repeat1,
    aux_sym_declaration_specifiers_repeat1,
    aux_sym_type_name_repeat1,
    aux_sym_struct_specifier_repeat1,
    aux_sym_declaration_repeat1,
    aux_sym_designation_repeat1,
    aux_sym_declarator_repeat1,
    aux_sym__direct_declarator_repeat1,
    aux_sym_compound_statement_repeat1,
    aux_sym_call_expression_repeat1,
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
    anon_sym_const,
    anon_sym_restrict,
    anon_sym_volatile,
    anon_sym_STAR,
    anon_sym_PLUS,
    sym_string,
    sym_identifier,
    sym_number,
    sym_comment,
};

static const char *ts_symbol_names[] = {
    [sym_program] = "program",
    [sym_function_definition] = "function_definition",
    [sym_declaration_specifiers] = "declaration_specifiers",
    [sym_storage_class_specifier] = "storage_class_specifier",
    [sym__type_specifier] = "_type_specifier",
    [sym_type_name] = "type_name",
    [sym_struct_specifier] = "struct_specifier",
    [sym_struct_declaration] = "struct_declaration",
    [sym_parameter_declaration] = "parameter_declaration",
    [sym_declaration] = "declaration",
    [sym__init_declarator] = "_init_declarator",
    [sym_initializer] = "initializer",
    [sym_initializer_list] = "initializer_list",
    [sym_designation] = "designation",
    [sym_declarator] = "declarator",
    [sym__direct_declarator] = "_direct_declarator",
    [sym_type_qualifier] = "type_qualifier",
    [sym_pointer] = "pointer",
    [sym_compound_statement] = "compound_statement",
    [sym_expression] = "expression",
    [sym_math_expression] = "math_expression",
    [sym_call_expression] = "call_expression",
    [sym_statement] = "statement",
    [sym_expression_statement] = "expression_statement",
    [aux_sym_function_definition_repeat1] = "function_definition_repeat1",
    [aux_sym_declaration_specifiers_repeat1] = "declaration_specifiers_repeat1",
    [aux_sym_type_name_repeat1] = "type_name_repeat1",
    [aux_sym_struct_specifier_repeat1] = "struct_specifier_repeat1",
    [aux_sym_declaration_repeat1] = "declaration_repeat1",
    [aux_sym_designation_repeat1] = "designation_repeat1",
    [aux_sym_declarator_repeat1] = "declarator_repeat1",
    [aux_sym__direct_declarator_repeat1] = "_direct_declarator_repeat1",
    [aux_sym_compound_statement_repeat1] = "compound_statement_repeat1",
    [aux_sym_call_expression_repeat1] = "call_expression_repeat1",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
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
    [anon_sym_const] = "const",
    [anon_sym_restrict] = "restrict",
    [anon_sym_volatile] = "volatile",
    [anon_sym_STAR] = "*",
    [anon_sym_PLUS] = "+",
    [sym_string] = "string",
    [sym_identifier] = "identifier",
    [sym_number] = "number",
    [sym_comment] = "comment",
};

static const TSNodeType ts_node_types[SYMBOL_COUNT] = {
    [sym_program] = TSNodeTypeNamed,
    [sym_function_definition] = TSNodeTypeNamed,
    [sym_declaration_specifiers] = TSNodeTypeNamed,
    [sym_storage_class_specifier] = TSNodeTypeNamed,
    [sym__type_specifier] = TSNodeTypeHidden,
    [sym_type_name] = TSNodeTypeNamed,
    [sym_struct_specifier] = TSNodeTypeNamed,
    [sym_struct_declaration] = TSNodeTypeNamed,
    [sym_parameter_declaration] = TSNodeTypeNamed,
    [sym_declaration] = TSNodeTypeNamed,
    [sym__init_declarator] = TSNodeTypeHidden,
    [sym_initializer] = TSNodeTypeNamed,
    [sym_initializer_list] = TSNodeTypeNamed,
    [sym_designation] = TSNodeTypeNamed,
    [sym_declarator] = TSNodeTypeNamed,
    [sym__direct_declarator] = TSNodeTypeHidden,
    [sym_type_qualifier] = TSNodeTypeNamed,
    [sym_pointer] = TSNodeTypeNamed,
    [sym_compound_statement] = TSNodeTypeNamed,
    [sym_expression] = TSNodeTypeNamed,
    [sym_math_expression] = TSNodeTypeNamed,
    [sym_call_expression] = TSNodeTypeNamed,
    [sym_statement] = TSNodeTypeNamed,
    [sym_expression_statement] = TSNodeTypeNamed,
    [aux_sym_function_definition_repeat1] = TSNodeTypeHidden,
    [aux_sym_declaration_specifiers_repeat1] = TSNodeTypeHidden,
    [aux_sym_type_name_repeat1] = TSNodeTypeHidden,
    [aux_sym_struct_specifier_repeat1] = TSNodeTypeHidden,
    [aux_sym_declaration_repeat1] = TSNodeTypeHidden,
    [aux_sym_designation_repeat1] = TSNodeTypeHidden,
    [aux_sym_declarator_repeat1] = TSNodeTypeHidden,
    [aux_sym__direct_declarator_repeat1] = TSNodeTypeHidden,
    [aux_sym_compound_statement_repeat1] = TSNodeTypeHidden,
    [aux_sym_call_expression_repeat1] = TSNodeTypeHidden,
    [ts_builtin_sym_error] = TSNodeTypeNamed,
    [ts_builtin_sym_end] = TSNodeTypeHidden,
    [anon_sym_typedef] = TSNodeTypeAnonymous,
    [anon_sym_extern] = TSNodeTypeAnonymous,
    [anon_sym_static] = TSNodeTypeAnonymous,
    [anon_sym_auto] = TSNodeTypeAnonymous,
    [anon_sym_register] = TSNodeTypeAnonymous,
    [anon_sym_signed] = TSNodeTypeAnonymous,
    [anon_sym_unsigned] = TSNodeTypeAnonymous,
    [anon_sym_long] = TSNodeTypeAnonymous,
    [anon_sym_short] = TSNodeTypeAnonymous,
    [anon_sym_struct] = TSNodeTypeAnonymous,
    [anon_sym_LBRACE] = TSNodeTypeAnonymous,
    [anon_sym_RBRACE] = TSNodeTypeAnonymous,
    [anon_sym_COMMA] = TSNodeTypeAnonymous,
    [anon_sym_SEMI] = TSNodeTypeAnonymous,
    [anon_sym_EQ] = TSNodeTypeAnonymous,
    [anon_sym_LBRACK] = TSNodeTypeAnonymous,
    [anon_sym_RBRACK] = TSNodeTypeAnonymous,
    [anon_sym_DOT] = TSNodeTypeAnonymous,
    [anon_sym_LPAREN] = TSNodeTypeAnonymous,
    [anon_sym_RPAREN] = TSNodeTypeAnonymous,
    [anon_sym_const] = TSNodeTypeAnonymous,
    [anon_sym_restrict] = TSNodeTypeAnonymous,
    [anon_sym_volatile] = TSNodeTypeAnonymous,
    [anon_sym_STAR] = TSNodeTypeAnonymous,
    [anon_sym_PLUS] = TSNodeTypeAnonymous,
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
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(1);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'a')
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(24);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(72);
            LEX_ERROR();
        case 2:
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 3:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(3);
            ACCEPT_TOKEN(sym_comment);
        case 4:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(sym_identifier);
        case 5:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'u')
                ADVANCE(6);
            ACCEPT_TOKEN(sym_identifier);
        case 6:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(7);
            ACCEPT_TOKEN(sym_identifier);
        case 7:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'o')
                ADVANCE(8);
            ACCEPT_TOKEN(sym_identifier);
        case 8:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_auto);
        case 9:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'o')
                ADVANCE(10);
            ACCEPT_TOKEN(sym_identifier);
        case 10:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'n')
                ADVANCE(11);
            ACCEPT_TOKEN(sym_identifier);
        case 11:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 's')
                ADVANCE(12);
            ACCEPT_TOKEN(sym_identifier);
        case 12:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(13);
            ACCEPT_TOKEN(sym_identifier);
        case 13:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_const);
        case 14:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'w') ||
                (lookahead == 'y') ||
                (lookahead == 'z'))
                ADVANCE(4);
            if (lookahead == 'x')
                ADVANCE(15);
            ACCEPT_TOKEN(sym_identifier);
        case 15:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(16);
            ACCEPT_TOKEN(sym_identifier);
        case 16:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'e')
                ADVANCE(17);
            ACCEPT_TOKEN(sym_identifier);
        case 17:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'r')
                ADVANCE(18);
            ACCEPT_TOKEN(sym_identifier);
        case 18:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'n')
                ADVANCE(19);
            ACCEPT_TOKEN(sym_identifier);
        case 19:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_extern);
        case 20:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'o')
                ADVANCE(21);
            ACCEPT_TOKEN(sym_identifier);
        case 21:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'n')
                ADVANCE(22);
            ACCEPT_TOKEN(sym_identifier);
        case 22:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'g')
                ADVANCE(23);
            ACCEPT_TOKEN(sym_identifier);
        case 23:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_long);
        case 24:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'e')
                ADVANCE(25);
            ACCEPT_TOKEN(sym_identifier);
        case 25:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'g')
                ADVANCE(26);
            if (lookahead == 's')
                ADVANCE(32);
            ACCEPT_TOKEN(sym_identifier);
        case 26:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'i')
                ADVANCE(27);
            ACCEPT_TOKEN(sym_identifier);
        case 27:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 's')
                ADVANCE(28);
            ACCEPT_TOKEN(sym_identifier);
        case 28:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(29);
            ACCEPT_TOKEN(sym_identifier);
        case 29:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'e')
                ADVANCE(30);
            ACCEPT_TOKEN(sym_identifier);
        case 30:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'r')
                ADVANCE(31);
            ACCEPT_TOKEN(sym_identifier);
        case 31:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_register);
        case 32:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(33);
            ACCEPT_TOKEN(sym_identifier);
        case 33:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'r')
                ADVANCE(34);
            ACCEPT_TOKEN(sym_identifier);
        case 34:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'i')
                ADVANCE(35);
            ACCEPT_TOKEN(sym_identifier);
        case 35:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'c')
                ADVANCE(36);
            ACCEPT_TOKEN(sym_identifier);
        case 36:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(37);
            ACCEPT_TOKEN(sym_identifier);
        case 37:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_restrict);
        case 38:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'h')
                ADVANCE(39);
            if (lookahead == 'i')
                ADVANCE(43);
            if (lookahead == 't')
                ADVANCE(48);
            ACCEPT_TOKEN(sym_identifier);
        case 39:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'o')
                ADVANCE(40);
            ACCEPT_TOKEN(sym_identifier);
        case 40:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'r')
                ADVANCE(41);
            ACCEPT_TOKEN(sym_identifier);
        case 41:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(42);
            ACCEPT_TOKEN(sym_identifier);
        case 42:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_short);
        case 43:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'g')
                ADVANCE(44);
            ACCEPT_TOKEN(sym_identifier);
        case 44:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'n')
                ADVANCE(45);
            ACCEPT_TOKEN(sym_identifier);
        case 45:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'e')
                ADVANCE(46);
            ACCEPT_TOKEN(sym_identifier);
        case 46:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'd')
                ADVANCE(47);
            ACCEPT_TOKEN(sym_identifier);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_signed);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'a')
                ADVANCE(49);
            if (lookahead == 'r')
                ADVANCE(53);
            ACCEPT_TOKEN(sym_identifier);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(50);
            ACCEPT_TOKEN(sym_identifier);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'i')
                ADVANCE(51);
            ACCEPT_TOKEN(sym_identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'c')
                ADVANCE(52);
            ACCEPT_TOKEN(sym_identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_static);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'u')
                ADVANCE(54);
            ACCEPT_TOKEN(sym_identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'c')
                ADVANCE(55);
            ACCEPT_TOKEN(sym_identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(56);
            ACCEPT_TOKEN(sym_identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_struct);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(4);
            if (lookahead == 'y')
                ADVANCE(58);
            ACCEPT_TOKEN(sym_identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'p')
                ADVANCE(59);
            ACCEPT_TOKEN(sym_identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'e')
                ADVANCE(60);
            ACCEPT_TOKEN(sym_identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'd')
                ADVANCE(61);
            ACCEPT_TOKEN(sym_identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'e')
                ADVANCE(62);
            ACCEPT_TOKEN(sym_identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'f')
                ADVANCE(63);
            ACCEPT_TOKEN(sym_identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_typedef);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'n')
                ADVANCE(65);
            ACCEPT_TOKEN(sym_identifier);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 's')
                ADVANCE(66);
            ACCEPT_TOKEN(sym_identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'i')
                ADVANCE(67);
            ACCEPT_TOKEN(sym_identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'g')
                ADVANCE(68);
            ACCEPT_TOKEN(sym_identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'n')
                ADVANCE(69);
            ACCEPT_TOKEN(sym_identifier);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'e')
                ADVANCE(70);
            ACCEPT_TOKEN(sym_identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'd')
                ADVANCE(71);
            ACCEPT_TOKEN(sym_identifier);
        case 71:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_unsigned);
        case 72:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'o')
                ADVANCE(73);
            ACCEPT_TOKEN(sym_identifier);
        case 73:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'l')
                ADVANCE(74);
            ACCEPT_TOKEN(sym_identifier);
        case 74:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'a')
                ADVANCE(75);
            ACCEPT_TOKEN(sym_identifier);
        case 75:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 't')
                ADVANCE(76);
            ACCEPT_TOKEN(sym_identifier);
        case 76:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'i')
                ADVANCE(77);
            ACCEPT_TOKEN(sym_identifier);
        case 77:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'l')
                ADVANCE(78);
            ACCEPT_TOKEN(sym_identifier);
        case 78:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'e')
                ADVANCE(79);
            ACCEPT_TOKEN(sym_identifier);
        case 79:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_volatile);
        case 80:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(81);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 81:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 82:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 's')
                ADVANCE(83);
            if (lookahead == 'u')
                ADVANCE(64);
            LEX_ERROR();
        case 83:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'h')
                ADVANCE(39);
            if (lookahead == 'i')
                ADVANCE(43);
            if (lookahead == 't')
                ADVANCE(84);
            ACCEPT_TOKEN(sym_identifier);
        case 84:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'r')
                ADVANCE(53);
            ACCEPT_TOKEN(sym_identifier);
        case 85:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(85);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            LEX_ERROR();
        case 86:
            ACCEPT_TOKEN(anon_sym_LPAREN);
        case 87:
            ACCEPT_TOKEN(anon_sym_STAR);
        case 88:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            LEX_ERROR();
        case 89:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(89);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 's')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(64);
            LEX_ERROR();
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'h')
                ADVANCE(39);
            if (lookahead == 'i')
                ADVANCE(43);
            ACCEPT_TOKEN(sym_identifier);
        case 91:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(91);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 92:
            ACCEPT_TOKEN(anon_sym_LBRACE);
        case 93:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(93);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 's')
                ADVANCE(83);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        case 94:
            ACCEPT_TOKEN(anon_sym_RBRACE);
        case 95:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(95);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 96:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        case 97:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(97);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '[')
                ADVANCE(98);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 's')
                ADVANCE(83);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        case 98:
            ACCEPT_TOKEN(anon_sym_LBRACK);
        case 99:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            LEX_ERROR();
        case 100:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 101:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 102:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(102);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '[')
                ADVANCE(98);
            LEX_ERROR();
        case 103:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == ']')
                ADVANCE(111);
            LEX_ERROR();
        case 104:
            if (lookahead == '\"')
                ADVANCE(105);
            if (lookahead == '\\')
                ADVANCE(106);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(104);
            LEX_ERROR();
        case 105:
            ACCEPT_TOKEN(sym_string);
        case 106:
            if (lookahead == '\"')
                ADVANCE(107);
            if (lookahead == '\\')
                ADVANCE(106);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(104);
            LEX_ERROR();
        case 107:
            if (lookahead == '\"')
                ADVANCE(105);
            if (lookahead == '\\')
                ADVANCE(106);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(104);
            ACCEPT_TOKEN(sym_string);
        case 108:
            if (lookahead == '.')
                ADVANCE(109);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            ACCEPT_TOKEN(sym_number);
        case 109:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(110);
            LEX_ERROR();
        case 110:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(110);
            ACCEPT_TOKEN(sym_number);
        case 111:
            ACCEPT_TOKEN(anon_sym_RBRACK);
        case 112:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(112);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'a')
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(24);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(72);
            LEX_ERROR();
        case 113:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 114:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 115:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '[')
                ADVANCE(98);
            LEX_ERROR();
        case 116:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(117);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ']')
                ADVANCE(111);
            LEX_ERROR();
        case 117:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 118:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(118);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            LEX_ERROR();
        case 119:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            LEX_ERROR();
        case 120:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(117);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 121:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(122);
            LEX_ERROR();
        case 122:
            ACCEPT_TOKEN(anon_sym_SEMI);
        case 123:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(123);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(122);
            if (lookahead == '=')
                ADVANCE(124);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'a')
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(24);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 124:
            ACCEPT_TOKEN(anon_sym_EQ);
        case 125:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(122);
            if (lookahead == '=')
                ADVANCE(124);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '[')
                ADVANCE(98);
            if (lookahead == 'a')
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(24);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 126:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'a')
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(24);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 127:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == 'a')
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(24);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        case 128:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 129:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(117);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(122);
            LEX_ERROR();
        case 130:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '.')
                ADVANCE(131);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '[')
                ADVANCE(98);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 131:
            ACCEPT_TOKEN(anon_sym_DOT);
        case 132:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(117);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        case 134:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '=')
                ADVANCE(124);
            LEX_ERROR();
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '.')
                ADVANCE(131);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '=')
                ADVANCE(124);
            if (lookahead == '[')
                ADVANCE(98);
            LEX_ERROR();
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '.')
                ADVANCE(131);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '[')
                ADVANCE(98);
            if (lookahead == '{')
                ADVANCE(92);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        case 137:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(117);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(122);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(117);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(122);
            if (lookahead == '=')
                ADVANCE(124);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(122);
            if (lookahead == '=')
                ADVANCE(124);
            if (lookahead == '[')
                ADVANCE(98);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(122);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(81);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(117);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '.')
                ADVANCE(131);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            if (lookahead == ';')
                ADVANCE(122);
            if (lookahead == '=')
                ADVANCE(124);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '[')
                ADVANCE(98);
            if (lookahead == ']')
                ADVANCE(111);
            if (lookahead == 'a')
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(24);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(92);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(81);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(117);
            if (lookahead == ',')
                ADVANCE(114);
            if (lookahead == '.')
                ADVANCE(131);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(108);
            if (lookahead == ';')
                ADVANCE(122);
            if (lookahead == '=')
                ADVANCE(124);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '[')
                ADVANCE(98);
            if (lookahead == ']')
                ADVANCE(111);
            if (lookahead == 'a')
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(14);
            if (lookahead == 'l')
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(24);
            if (lookahead == 's')
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(57);
            if (lookahead == 'u')
                ADVANCE(64);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(92);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 80,
    [2] = 80,
    [3] = 82,
    [4] = 1,
    [5] = 85,
    [6] = 85,
    [7] = 82,
    [8] = 88,
    [9] = 1,
    [10] = 89,
    [11] = 91,
    [12] = 1,
    [13] = 85,
    [14] = 93,
    [15] = 95,
    [16] = 93,
    [17] = 85,
    [18] = 85,
    [19] = 93,
    [20] = 88,
    [21] = 96,
    [22] = 91,
    [23] = 85,
    [24] = 85,
    [25] = 93,
    [26] = 95,
    [27] = 93,
    [28] = 96,
    [29] = 85,
    [30] = 85,
    [31] = 96,
    [32] = 85,
    [33] = 85,
    [34] = 85,
    [35] = 96,
    [36] = 93,
    [37] = 97,
    [38] = 85,
    [39] = 99,
    [40] = 85,
    [41] = 85,
    [42] = 97,
    [43] = 100,
    [44] = 102,
    [45] = 99,
    [46] = 85,
    [47] = 102,
    [48] = 100,
    [49] = 102,
    [50] = 102,
    [51] = 103,
    [52] = 112,
    [53] = 82,
    [54] = 85,
    [55] = 113,
    [56] = 100,
    [57] = 1,
    [58] = 102,
    [59] = 113,
    [60] = 100,
    [61] = 102,
    [62] = 113,
    [63] = 115,
    [64] = 99,
    [65] = 85,
    [66] = 115,
    [67] = 100,
    [68] = 115,
    [69] = 115,
    [70] = 103,
    [71] = 112,
    [72] = 113,
    [73] = 100,
    [74] = 115,
    [75] = 115,
    [76] = 116,
    [77] = 116,
    [78] = 118,
    [79] = 119,
    [80] = 119,
    [81] = 116,
    [82] = 116,
    [83] = 120,
    [84] = 120,
    [85] = 116,
    [86] = 100,
    [87] = 119,
    [88] = 118,
    [89] = 116,
    [90] = 119,
    [91] = 119,
    [92] = 120,
    [93] = 120,
    [94] = 120,
    [95] = 120,
    [96] = 100,
    [97] = 120,
    [98] = 120,
    [99] = 120,
    [100] = 100,
    [101] = 116,
    [102] = 85,
    [103] = 113,
    [104] = 116,
    [105] = 97,
    [106] = 97,
    [107] = 103,
    [108] = 112,
    [109] = 113,
    [110] = 100,
    [111] = 97,
    [112] = 97,
    [113] = 116,
    [114] = 99,
    [115] = 96,
    [116] = 85,
    [117] = 88,
    [118] = 85,
    [119] = 121,
    [120] = 123,
    [121] = 125,
    [122] = 99,
    [123] = 85,
    [124] = 125,
    [125] = 100,
    [126] = 125,
    [127] = 125,
    [128] = 103,
    [129] = 112,
    [130] = 113,
    [131] = 100,
    [132] = 125,
    [133] = 125,
    [134] = 116,
    [135] = 82,
    [136] = 85,
    [137] = 126,
    [138] = 80,
    [139] = 95,
    [140] = 127,
    [141] = 128,
    [142] = 121,
    [143] = 129,
    [144] = 129,
    [145] = 130,
    [146] = 132,
    [147] = 132,
    [148] = 128,
    [149] = 133,
    [150] = 133,
    [151] = 134,
    [152] = 130,
    [153] = 119,
    [154] = 88,
    [155] = 135,
    [156] = 134,
    [157] = 116,
    [158] = 135,
    [159] = 134,
    [160] = 132,
    [161] = 132,
    [162] = 136,
    [163] = 132,
    [164] = 128,
    [165] = 132,
    [166] = 132,
    [167] = 128,
    [168] = 118,
    [169] = 119,
    [170] = 119,
    [171] = 133,
    [172] = 133,
    [173] = 120,
    [174] = 133,
    [175] = 100,
    [176] = 133,
    [177] = 133,
    [178] = 132,
    [179] = 121,
    [180] = 136,
    [181] = 121,
    [182] = 118,
    [183] = 119,
    [184] = 119,
    [185] = 129,
    [186] = 129,
    [187] = 120,
    [188] = 129,
    [189] = 100,
    [190] = 129,
    [191] = 129,
    [192] = 82,
    [193] = 85,
    [194] = 127,
    [195] = 137,
    [196] = 137,
    [197] = 127,
    [198] = 96,
    [199] = 80,
    [200] = 138,
    [201] = 80,
    [202] = 127,
    [203] = 118,
    [204] = 119,
    [205] = 119,
    [206] = 137,
    [207] = 137,
    [208] = 120,
    [209] = 137,
    [210] = 100,
    [211] = 137,
    [212] = 137,
    [213] = 96,
    [214] = 121,
    [215] = 139,
    [216] = 140,
    [217] = 99,
    [218] = 85,
    [219] = 140,
    [220] = 100,
    [221] = 140,
    [222] = 140,
    [223] = 103,
    [224] = 112,
    [225] = 113,
    [226] = 100,
    [227] = 140,
    [228] = 140,
    [229] = 116,
    [230] = 141,
    [231] = 85,
    [232] = 127,
    [233] = 121,
    [234] = 141,
    [235] = 127,
    [236] = 85,
    [237] = 121,
    [238] = 141,
    [239] = 127,
    [240] = 80,
    [241] = 95,
    [242] = 121,
    [243] = 141,
    [244] = 126,
    [245] = 126,
    [246] = 85,
    [247] = 121,
    [248] = 141,
    [249] = 126,
    [250] = 141,
    [251] = 80,
    [252] = 80,
    [253] = 82,
    [254] = 85,
    [255] = 121,
    [256] = 123,
    [257] = 95,
    [258] = 80,
    [259] = 141,
    [260] = 80,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction *ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = ACTIONS(SHIFT(1)),
        [sym_function_definition] = ACTIONS(SHIFT(2)),
        [sym_declaration_specifiers] = ACTIONS(SHIFT(3)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(5)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(2)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(11)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(13)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [1] = {
        [ts_builtin_sym_end] = ACTIONS(ACCEPT_INPUT()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [2] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [3] = {
        [sym__type_specifier] = ACTIONS(SHIFT(254)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(13)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [4] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_name] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(253)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [5] = {
        [sym__init_declarator] = ACTIONS(SHIFT(119)),
        [sym_declarator] = ACTIONS(SHIFT(120)),
        [sym__direct_declarator] = ACTIONS(SHIFT(121)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(122)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(124)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [7] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
        [sym_identifier] = ACTIONS(SHIFT(118)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
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
    [10] = {
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(117)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
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
    [13] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [sym__type_specifier] = ACTIONS(SHIFT(17)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_struct_declaration] = ACTIONS(SHIFT(19)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(115)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(116)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [15] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym__type_specifier] = ACTIONS(SHIFT(17)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_struct_declaration] = ACTIONS(SHIFT(19)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(21)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(23)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [sym_declarator] = ACTIONS(SHIFT(36)),
        [sym__direct_declarator] = ACTIONS(SHIFT(37)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(39)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(40)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(42)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [sym_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [sym__type_specifier] = ACTIONS(SHIFT(17)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_struct_declaration] = ACTIONS(SHIFT(19)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(35)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [sym_identifier] = ACTIONS(SHIFT(34)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(33)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(25)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [sym__type_specifier] = ACTIONS(SHIFT(17)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_struct_declaration] = ACTIONS(SHIFT(19)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(32)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [sym__type_specifier] = ACTIONS(SHIFT(17)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_struct_declaration] = ACTIONS(SHIFT(19)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(28)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(29)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(30)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(29)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [33] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [34] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [35] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [36] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [37] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(107)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(108)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [38] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(114)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [39] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(106)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(42)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [40] = {
        [sym_declarator] = ACTIONS(SHIFT(43)),
        [sym__direct_declarator] = ACTIONS(SHIFT(44)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(45)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(46)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(47)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [41] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_pointer, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [42] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [43] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(105)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [44] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(51)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(52)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [45] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(50)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(46)),
        [sym_identifier] = ACTIONS(SHIFT(47)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [46] = {
        [sym_declarator] = ACTIONS(SHIFT(48)),
        [sym__direct_declarator] = ACTIONS(SHIFT(44)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(45)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(46)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(47)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [47] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [48] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(49)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [49] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [50] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(51)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(52)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [51] = {
        [sym_expression] = ACTIONS(SHIFT(104)),
        [sym_math_expression] = ACTIONS(SHIFT(77)),
        [sym_call_expression] = ACTIONS(SHIFT(77)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(49)),
        [sym_string] = ACTIONS(SHIFT(77)),
        [sym_identifier] = ACTIONS(SHIFT(77)),
        [sym_number] = ACTIONS(SHIFT(77)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [52] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(53)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(54)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(55)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(49)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [53] = {
        [sym__type_specifier] = ACTIONS(SHIFT(102)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [54] = {
        [sym_declarator] = ACTIONS(SHIFT(62)),
        [sym__direct_declarator] = ACTIONS(SHIFT(63)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(64)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(65)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(66)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [55] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(56)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(57)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(58)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [56] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(61)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [57] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(53)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(54)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(59)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [58] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [59] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(60)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(57)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__direct_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [60] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__direct_declarator_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [61] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [62] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [63] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(70)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(71)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [64] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(65)),
        [sym_identifier] = ACTIONS(SHIFT(66)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [65] = {
        [sym_declarator] = ACTIONS(SHIFT(67)),
        [sym__direct_declarator] = ACTIONS(SHIFT(44)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(45)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(46)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(47)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [66] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [67] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(68)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [68] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [69] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(70)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(71)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [70] = {
        [sym_expression] = ACTIONS(SHIFT(76)),
        [sym_math_expression] = ACTIONS(SHIFT(77)),
        [sym_call_expression] = ACTIONS(SHIFT(77)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(68)),
        [sym_string] = ACTIONS(SHIFT(77)),
        [sym_identifier] = ACTIONS(SHIFT(77)),
        [sym_number] = ACTIONS(SHIFT(77)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [71] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(53)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(54)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(72)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(68)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [72] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(73)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(57)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(74)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [75] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(74)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(78)),
        [anon_sym_STAR] = ACTIONS(SHIFT(79)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [sym_expression] = ACTIONS(SHIFT(83)),
        [sym_math_expression] = ACTIONS(SHIFT(84)),
        [sym_call_expression] = ACTIONS(SHIFT(84)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(85)),
        [sym_string] = ACTIONS(SHIFT(84)),
        [sym_identifier] = ACTIONS(SHIFT(84)),
        [sym_number] = ACTIONS(SHIFT(84)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [sym_expression] = ACTIONS(SHIFT(82)),
        [sym_math_expression] = ACTIONS(SHIFT(77)),
        [sym_call_expression] = ACTIONS(SHIFT(77)),
        [sym_string] = ACTIONS(SHIFT(77)),
        [sym_identifier] = ACTIONS(SHIFT(77)),
        [sym_number] = ACTIONS(SHIFT(77)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [80] = {
        [sym_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(77)),
        [sym_call_expression] = ACTIONS(SHIFT(77)),
        [sym_string] = ACTIONS(SHIFT(77)),
        [sym_identifier] = ACTIONS(SHIFT(77)),
        [sym_number] = ACTIONS(SHIFT(77)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(78)),
        [anon_sym_STAR] = ACTIONS(SHIFT(79)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [82] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(78)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(86)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(87)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(88)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(89)),
        [anon_sym_STAR] = ACTIONS(SHIFT(90)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(91)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [sym_expression] = ACTIONS(SHIFT(99)),
        [sym_math_expression] = ACTIONS(SHIFT(84)),
        [sym_call_expression] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(84)),
        [sym_identifier] = ACTIONS(SHIFT(84)),
        [sym_number] = ACTIONS(SHIFT(84)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [sym_expression] = ACTIONS(SHIFT(94)),
        [sym_math_expression] = ACTIONS(SHIFT(84)),
        [sym_call_expression] = ACTIONS(SHIFT(84)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(84)),
        [sym_identifier] = ACTIONS(SHIFT(84)),
        [sym_number] = ACTIONS(SHIFT(84)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [sym_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(84)),
        [sym_call_expression] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(84)),
        [sym_identifier] = ACTIONS(SHIFT(84)),
        [sym_number] = ACTIONS(SHIFT(84)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [sym_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(84)),
        [sym_call_expression] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(84)),
        [sym_identifier] = ACTIONS(SHIFT(84)),
        [sym_number] = ACTIONS(SHIFT(84)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(88)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(90)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(88)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(96)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(87)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(88)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_STAR] = ACTIONS(SHIFT(90)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(91)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(98)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [99] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(100)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(87)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(88)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(90)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(91)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
        [sym_declarator] = ACTIONS(SHIFT(103)),
        [sym__direct_declarator] = ACTIONS(SHIFT(63)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(64)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(65)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(66)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [103] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(58)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(78)),
        [anon_sym_STAR] = ACTIONS(SHIFT(79)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [106] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(107)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(108)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [107] = {
        [sym_expression] = ACTIONS(SHIFT(113)),
        [sym_math_expression] = ACTIONS(SHIFT(77)),
        [sym_call_expression] = ACTIONS(SHIFT(77)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(105)),
        [sym_string] = ACTIONS(SHIFT(77)),
        [sym_identifier] = ACTIONS(SHIFT(77)),
        [sym_number] = ACTIONS(SHIFT(77)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [108] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(53)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(54)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(109)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(105)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(110)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(57)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(111)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(112)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(111)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(78)),
        [anon_sym_STAR] = ACTIONS(SHIFT(79)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [116] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [117] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [119] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(250)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(231)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [120] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(135)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(136)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(137)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(138)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(139)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(11)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(140)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(13)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [121] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(128)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(129)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [122] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(127)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [sym_identifier] = ACTIONS(SHIFT(124)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [123] = {
        [sym_declarator] = ACTIONS(SHIFT(125)),
        [sym__direct_declarator] = ACTIONS(SHIFT(44)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(45)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(46)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(47)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [124] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [125] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(126)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(128)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(129)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [sym_expression] = ACTIONS(SHIFT(134)),
        [sym_math_expression] = ACTIONS(SHIFT(77)),
        [sym_call_expression] = ACTIONS(SHIFT(77)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(126)),
        [sym_string] = ACTIONS(SHIFT(77)),
        [sym_identifier] = ACTIONS(SHIFT(77)),
        [sym_number] = ACTIONS(SHIFT(77)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(53)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(54)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(130)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(126)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(131)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(57)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(132)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [131] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_const] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [133] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_const] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(132)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(78)),
        [anon_sym_STAR] = ACTIONS(SHIFT(79)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [sym__type_specifier] = ACTIONS(SHIFT(246)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(13)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [sym__init_declarator] = ACTIONS(SHIFT(242)),
        [sym_declarator] = ACTIONS(SHIFT(215)),
        [sym__direct_declarator] = ACTIONS(SHIFT(216)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(217)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(218)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(219)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(135)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(136)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(137)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(241)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(11)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(13)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [139] = {
        [sym_compound_statement] = ACTIONS(SHIFT(240)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(140)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [140] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(192)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(193)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(194)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(195)),
        [sym_math_expression] = ACTIONS(SHIFT(196)),
        [sym_call_expression] = ACTIONS(SHIFT(196)),
        [sym_statement] = ACTIONS(SHIFT(194)),
        [sym_expression_statement] = ACTIONS(SHIFT(197)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(198)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(11)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(199)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_string] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(200)),
        [sym_number] = ACTIONS(SHIFT(196)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [sym_initializer] = ACTIONS(SHIFT(142)),
        [sym_expression] = ACTIONS(SHIFT(143)),
        [sym_math_expression] = ACTIONS(SHIFT(144)),
        [sym_call_expression] = ACTIONS(SHIFT(144)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(145)),
        [sym_string] = ACTIONS(SHIFT(144)),
        [sym_identifier] = ACTIONS(SHIFT(144)),
        [sym_number] = ACTIONS(SHIFT(144)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(182)),
        [anon_sym_STAR] = ACTIONS(SHIFT(183)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(184)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [144] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [145] = {
        [sym_initializer] = ACTIONS(SHIFT(146)),
        [sym_initializer_list] = ACTIONS(SHIFT(147)),
        [sym_designation] = ACTIONS(SHIFT(148)),
        [sym_expression] = ACTIONS(SHIFT(149)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(151)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(152)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(153)),
        [anon_sym_DOT] = ACTIONS(SHIFT(154)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(179)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(180)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [sym_initializer] = ACTIONS(SHIFT(178)),
        [sym_expression] = ACTIONS(SHIFT(149)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(152)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(168)),
        [anon_sym_STAR] = ACTIONS(SHIFT(169)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(167)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [sym_initializer] = ACTIONS(SHIFT(146)),
        [sym_initializer_list] = ACTIONS(SHIFT(160)),
        [sym_designation] = ACTIONS(SHIFT(148)),
        [sym_expression] = ACTIONS(SHIFT(149)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(151)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(152)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(153)),
        [anon_sym_DOT] = ACTIONS(SHIFT(154)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [sym_expression] = ACTIONS(SHIFT(157)),
        [sym_math_expression] = ACTIONS(SHIFT(77)),
        [sym_call_expression] = ACTIONS(SHIFT(77)),
        [sym_string] = ACTIONS(SHIFT(77)),
        [sym_identifier] = ACTIONS(SHIFT(77)),
        [sym_number] = ACTIONS(SHIFT(77)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym_identifier] = ACTIONS(SHIFT(155)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(156)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(153)),
        [anon_sym_DOT] = ACTIONS(SHIFT(154)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(158)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(78)),
        [anon_sym_STAR] = ACTIONS(SHIFT(79)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(159)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(153)),
        [anon_sym_DOT] = ACTIONS(SHIFT(154)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(161)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(162)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [sym_initializer] = ACTIONS(SHIFT(163)),
        [sym_designation] = ACTIONS(SHIFT(164)),
        [sym_expression] = ACTIONS(SHIFT(149)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(151)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(152)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(165)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(153)),
        [anon_sym_DOT] = ACTIONS(SHIFT(154)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [sym_initializer] = ACTIONS(SHIFT(166)),
        [sym_expression] = ACTIONS(SHIFT(149)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(152)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [sym_expression] = ACTIONS(SHIFT(173)),
        [sym_math_expression] = ACTIONS(SHIFT(84)),
        [sym_call_expression] = ACTIONS(SHIFT(84)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(174)),
        [sym_string] = ACTIONS(SHIFT(84)),
        [sym_identifier] = ACTIONS(SHIFT(84)),
        [sym_number] = ACTIONS(SHIFT(84)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [sym_expression] = ACTIONS(SHIFT(172)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [sym_expression] = ACTIONS(SHIFT(171)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(168)),
        [anon_sym_STAR] = ACTIONS(SHIFT(169)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [172] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(168)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(175)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(87)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(88)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(176)),
        [anon_sym_STAR] = ACTIONS(SHIFT(90)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(91)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(177)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [180] = {
        [sym_initializer] = ACTIONS(SHIFT(163)),
        [sym_designation] = ACTIONS(SHIFT(164)),
        [sym_expression] = ACTIONS(SHIFT(149)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(151)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(152)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(181)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(153)),
        [anon_sym_DOT] = ACTIONS(SHIFT(154)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [sym_expression] = ACTIONS(SHIFT(187)),
        [sym_math_expression] = ACTIONS(SHIFT(84)),
        [sym_call_expression] = ACTIONS(SHIFT(84)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(188)),
        [sym_string] = ACTIONS(SHIFT(84)),
        [sym_identifier] = ACTIONS(SHIFT(84)),
        [sym_number] = ACTIONS(SHIFT(84)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [sym_expression] = ACTIONS(SHIFT(186)),
        [sym_math_expression] = ACTIONS(SHIFT(144)),
        [sym_call_expression] = ACTIONS(SHIFT(144)),
        [sym_string] = ACTIONS(SHIFT(144)),
        [sym_identifier] = ACTIONS(SHIFT(144)),
        [sym_number] = ACTIONS(SHIFT(144)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
        [sym_expression] = ACTIONS(SHIFT(185)),
        [sym_math_expression] = ACTIONS(SHIFT(144)),
        [sym_call_expression] = ACTIONS(SHIFT(144)),
        [sym_string] = ACTIONS(SHIFT(144)),
        [sym_identifier] = ACTIONS(SHIFT(144)),
        [sym_number] = ACTIONS(SHIFT(144)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [185] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(182)),
        [anon_sym_STAR] = ACTIONS(SHIFT(183)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [186] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(182)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(189)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(87)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(88)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(190)),
        [anon_sym_STAR] = ACTIONS(SHIFT(90)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(91)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [188] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(191)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [sym__type_specifier] = ACTIONS(SHIFT(236)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(13)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [sym__init_declarator] = ACTIONS(SHIFT(214)),
        [sym_declarator] = ACTIONS(SHIFT(215)),
        [sym__direct_declarator] = ACTIONS(SHIFT(216)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(217)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(218)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(219)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(192)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(193)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(194)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(195)),
        [sym_math_expression] = ACTIONS(SHIFT(196)),
        [sym_call_expression] = ACTIONS(SHIFT(196)),
        [sym_statement] = ACTIONS(SHIFT(194)),
        [sym_expression_statement] = ACTIONS(SHIFT(197)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(213)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(11)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_string] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(200)),
        [sym_number] = ACTIONS(SHIFT(196)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(202)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(203)),
        [anon_sym_STAR] = ACTIONS(SHIFT(204)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(205)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_expression] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_statement] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_statement, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_string] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1), REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 1), REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
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
        [anon_sym_struct] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
        [sym_expression] = ACTIONS(SHIFT(208)),
        [sym_math_expression] = ACTIONS(SHIFT(84)),
        [sym_call_expression] = ACTIONS(SHIFT(84)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(209)),
        [sym_string] = ACTIONS(SHIFT(84)),
        [sym_identifier] = ACTIONS(SHIFT(84)),
        [sym_number] = ACTIONS(SHIFT(84)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
        [sym_expression] = ACTIONS(SHIFT(207)),
        [sym_math_expression] = ACTIONS(SHIFT(196)),
        [sym_call_expression] = ACTIONS(SHIFT(196)),
        [sym_string] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(196)),
        [sym_number] = ACTIONS(SHIFT(196)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [sym_expression] = ACTIONS(SHIFT(206)),
        [sym_math_expression] = ACTIONS(SHIFT(196)),
        [sym_call_expression] = ACTIONS(SHIFT(196)),
        [sym_string] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(196)),
        [sym_number] = ACTIONS(SHIFT(196)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(203)),
        [anon_sym_STAR] = ACTIONS(SHIFT(204)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(203)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(210)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(87)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(88)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(211)),
        [anon_sym_STAR] = ACTIONS(SHIFT(90)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(91)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [209] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(212)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [213] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(230)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(231)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(232)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(223)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(222)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(218)),
        [sym_identifier] = ACTIONS(SHIFT(219)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
        [sym_declarator] = ACTIONS(SHIFT(220)),
        [sym__direct_declarator] = ACTIONS(SHIFT(44)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(45)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(46)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(47)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [219] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(223)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
        [sym_expression] = ACTIONS(SHIFT(229)),
        [sym_math_expression] = ACTIONS(SHIFT(77)),
        [sym_call_expression] = ACTIONS(SHIFT(77)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(221)),
        [sym_string] = ACTIONS(SHIFT(77)),
        [sym_identifier] = ACTIONS(SHIFT(77)),
        [sym_number] = ACTIONS(SHIFT(77)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(53)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(54)),
        [sym_type_name] = ACTIONS(SHIFT(18)),
        [sym_struct_specifier] = ACTIONS(SHIFT(18)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(225)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(22)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(221)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [225] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(226)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(57)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(227)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(228)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [228] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(227)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(78)),
        [anon_sym_STAR] = ACTIONS(SHIFT(79)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [231] = {
        [sym__init_declarator] = ACTIONS(SHIFT(233)),
        [sym_declarator] = ACTIONS(SHIFT(215)),
        [sym__direct_declarator] = ACTIONS(SHIFT(216)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(217)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(218)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(219)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
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
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [233] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(234)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(231)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
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
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
        [sym__init_declarator] = ACTIONS(SHIFT(237)),
        [sym_declarator] = ACTIONS(SHIFT(215)),
        [sym__direct_declarator] = ACTIONS(SHIFT(216)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(217)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(218)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(219)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [237] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(238)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(231)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [238] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
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
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [240] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [241] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(243)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(231)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(244)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [243] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(245)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
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
    [245] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
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
    [246] = {
        [sym__init_declarator] = ACTIONS(SHIFT(247)),
        [sym_declarator] = ACTIONS(SHIFT(215)),
        [sym__direct_declarator] = ACTIONS(SHIFT(216)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(217)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(218)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(219)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [247] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(248)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(231)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(245)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(249)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
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
    [250] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(252)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_type_name] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [sym__init_declarator] = ACTIONS(SHIFT(255)),
        [sym_declarator] = ACTIONS(SHIFT(256)),
        [sym__direct_declarator] = ACTIONS(SHIFT(121)),
        [sym_pointer] = ACTIONS(SHIFT(38)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(122)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(41)),
        [sym_identifier] = ACTIONS(SHIFT(124)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(259)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(231)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(252)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(135)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(136)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(137)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(240)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(257)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_typedef] = ACTIONS(SHIFT(9)),
        [anon_sym_extern] = ACTIONS(SHIFT(9)),
        [anon_sym_static] = ACTIONS(SHIFT(9)),
        [anon_sym_auto] = ACTIONS(SHIFT(9)),
        [anon_sym_register] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(10)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(10)),
        [anon_sym_long] = ACTIONS(SHIFT(10)),
        [anon_sym_short] = ACTIONS(SHIFT(10)),
        [anon_sym_struct] = ACTIONS(SHIFT(11)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(140)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_const] = ACTIONS(SHIFT(12)),
        [anon_sym_restrict] = ACTIONS(SHIFT(12)),
        [anon_sym_volatile] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(SHIFT(13)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [sym_compound_statement] = ACTIONS(SHIFT(258)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(140)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [259] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(260)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [260] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
