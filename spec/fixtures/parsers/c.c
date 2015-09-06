#include "tree_sitter/parser.h"

#define STATE_COUNT 270
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
    aux_sym_typedef,
    aux_sym_extern,
    aux_sym_static,
    aux_sym_auto,
    aux_sym_register,
    aux_sym_signed,
    aux_sym_unsigned,
    aux_sym_long,
    aux_sym_short,
    aux_sym_struct,
    aux_sym_LBRACE,
    aux_sym_RBRACE,
    aux_sym_COMMA,
    aux_sym_SEMI,
    aux_sym_EQ,
    aux_sym_LBRACK,
    aux_sym_RBRACK,
    aux_sym_DOT,
    aux_sym_LPAREN,
    aux_sym_RPAREN,
    aux_sym_const,
    aux_sym_restrict,
    aux_sym_volatile,
    aux_sym_STAR,
    aux_sym_PLUS,
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
    [aux_sym_typedef] = "typedef",
    [aux_sym_extern] = "extern",
    [aux_sym_static] = "static",
    [aux_sym_auto] = "auto",
    [aux_sym_register] = "register",
    [aux_sym_signed] = "signed",
    [aux_sym_unsigned] = "unsigned",
    [aux_sym_long] = "long",
    [aux_sym_short] = "short",
    [aux_sym_struct] = "struct",
    [aux_sym_LBRACE] = "{",
    [aux_sym_RBRACE] = "}",
    [aux_sym_COMMA] = ",",
    [aux_sym_SEMI] = ";",
    [aux_sym_EQ] = "=",
    [aux_sym_LBRACK] = "[",
    [aux_sym_RBRACK] = "]",
    [aux_sym_DOT] = ".",
    [aux_sym_LPAREN] = "(",
    [aux_sym_RPAREN] = ")",
    [aux_sym_const] = "const",
    [aux_sym_restrict] = "restrict",
    [aux_sym_volatile] = "volatile",
    [aux_sym_STAR] = "*",
    [aux_sym_PLUS] = "+",
    [sym_string] = "string",
    [sym_identifier] = "identifier",
    [sym_number] = "number",
    [sym_comment] = "comment",
};

static const TSNodeType ts_node_types[SYMBOL_COUNT] = {
    [sym_program] = TSNodeTypeNormal,
    [sym_function_definition] = TSNodeTypeNormal,
    [sym_declaration_specifiers] = TSNodeTypeNormal,
    [sym_storage_class_specifier] = TSNodeTypeNormal,
    [sym__type_specifier] = TSNodeTypeHidden,
    [sym_type_name] = TSNodeTypeNormal,
    [sym_struct_specifier] = TSNodeTypeNormal,
    [sym_struct_declaration] = TSNodeTypeNormal,
    [sym_parameter_declaration] = TSNodeTypeNormal,
    [sym_declaration] = TSNodeTypeNormal,
    [sym__init_declarator] = TSNodeTypeHidden,
    [sym_initializer] = TSNodeTypeNormal,
    [sym_initializer_list] = TSNodeTypeNormal,
    [sym_designation] = TSNodeTypeNormal,
    [sym_declarator] = TSNodeTypeNormal,
    [sym__direct_declarator] = TSNodeTypeHidden,
    [sym_type_qualifier] = TSNodeTypeNormal,
    [sym_pointer] = TSNodeTypeNormal,
    [sym_compound_statement] = TSNodeTypeNormal,
    [sym_expression] = TSNodeTypeNormal,
    [sym_math_expression] = TSNodeTypeNormal,
    [sym_call_expression] = TSNodeTypeNormal,
    [sym_statement] = TSNodeTypeNormal,
    [sym_expression_statement] = TSNodeTypeNormal,
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
    [ts_builtin_sym_error] = TSNodeTypeNormal,
    [ts_builtin_sym_end] = TSNodeTypeHidden,
    [aux_sym_typedef] = TSNodeTypeConcrete,
    [aux_sym_extern] = TSNodeTypeConcrete,
    [aux_sym_static] = TSNodeTypeConcrete,
    [aux_sym_auto] = TSNodeTypeConcrete,
    [aux_sym_register] = TSNodeTypeConcrete,
    [aux_sym_signed] = TSNodeTypeConcrete,
    [aux_sym_unsigned] = TSNodeTypeConcrete,
    [aux_sym_long] = TSNodeTypeConcrete,
    [aux_sym_short] = TSNodeTypeConcrete,
    [aux_sym_struct] = TSNodeTypeConcrete,
    [aux_sym_LBRACE] = TSNodeTypeConcrete,
    [aux_sym_RBRACE] = TSNodeTypeConcrete,
    [aux_sym_COMMA] = TSNodeTypeConcrete,
    [aux_sym_SEMI] = TSNodeTypeConcrete,
    [aux_sym_EQ] = TSNodeTypeConcrete,
    [aux_sym_LBRACK] = TSNodeTypeConcrete,
    [aux_sym_RBRACK] = TSNodeTypeConcrete,
    [aux_sym_DOT] = TSNodeTypeConcrete,
    [aux_sym_LPAREN] = TSNodeTypeConcrete,
    [aux_sym_RPAREN] = TSNodeTypeConcrete,
    [aux_sym_const] = TSNodeTypeConcrete,
    [aux_sym_restrict] = TSNodeTypeConcrete,
    [aux_sym_volatile] = TSNodeTypeConcrete,
    [aux_sym_STAR] = TSNodeTypeConcrete,
    [aux_sym_PLUS] = TSNodeTypeConcrete,
    [sym_string] = TSNodeTypeNormal,
    [sym_identifier] = TSNodeTypeNormal,
    [sym_number] = TSNodeTypeNormal,
    [sym_comment] = TSNodeTypeNormal,
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
            ACCEPT_TOKEN(aux_sym_auto);
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
            ACCEPT_TOKEN(aux_sym_const);
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
            ACCEPT_TOKEN(aux_sym_extern);
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
            ACCEPT_TOKEN(aux_sym_long);
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
            ACCEPT_TOKEN(aux_sym_register);
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
            ACCEPT_TOKEN(aux_sym_restrict);
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
            ACCEPT_TOKEN(aux_sym_short);
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
            ACCEPT_TOKEN(aux_sym_signed);
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
            ACCEPT_TOKEN(aux_sym_static);
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
            ACCEPT_TOKEN(aux_sym_struct);
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
            ACCEPT_TOKEN(aux_sym_typedef);
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
            ACCEPT_TOKEN(aux_sym_unsigned);
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
            ACCEPT_TOKEN(aux_sym_volatile);
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
            ACCEPT_TOKEN(aux_sym_LPAREN);
        case 87:
            ACCEPT_TOKEN(aux_sym_STAR);
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
            ACCEPT_TOKEN(aux_sym_LBRACE);
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
            ACCEPT_TOKEN(aux_sym_RBRACE);
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
            ACCEPT_TOKEN(aux_sym_LBRACK);
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
            ACCEPT_TOKEN(aux_sym_RPAREN);
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
                ADVANCE(109);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == ']')
                ADVANCE(112);
            LEX_ERROR();
        case 104:
            if (lookahead == '\"')
                ADVANCE(105);
            if (lookahead == '\\')
                ADVANCE(106);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(108);
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
                ADVANCE(108);
            LEX_ERROR();
        case 107:
            if (lookahead == '\"')
                ADVANCE(105);
            if (lookahead == '\\')
                ADVANCE(106);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(108);
            ACCEPT_TOKEN(sym_string);
        case 108:
            if (lookahead == '\"')
                ADVANCE(105);
            if (lookahead == '\\')
                ADVANCE(106);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(108);
            LEX_ERROR();
        case 109:
            if (lookahead == '.')
                ADVANCE(110);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
            ACCEPT_TOKEN(sym_number);
        case 110:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(111);
            LEX_ERROR();
        case 111:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(111);
            ACCEPT_TOKEN(sym_number);
        case 112:
            ACCEPT_TOKEN(aux_sym_RBRACK);
        case 113:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
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
        case 114:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(114);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 115:
            ACCEPT_TOKEN(aux_sym_COMMA);
        case 116:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '[')
                ADVANCE(98);
            LEX_ERROR();
        case 117:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(118);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ']')
                ADVANCE(112);
            LEX_ERROR();
        case 118:
            ACCEPT_TOKEN(aux_sym_PLUS);
        case 119:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
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
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            LEX_ERROR();
        case 121:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(118);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 122:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(122);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(123);
            LEX_ERROR();
        case 123:
            ACCEPT_TOKEN(aux_sym_SEMI);
        case 124:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(124);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(123);
            if (lookahead == '=')
                ADVANCE(125);
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
        case 125:
            ACCEPT_TOKEN(aux_sym_EQ);
        case 126:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(123);
            if (lookahead == '=')
                ADVANCE(125);
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
        case 127:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
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
                ADVANCE(109);
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
        case 129:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 130:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(118);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(123);
            LEX_ERROR();
        case 131:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(131);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '.')
                ADVANCE(132);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            if (lookahead == '[')
                ADVANCE(98);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 132:
            ACCEPT_TOKEN(aux_sym_DOT);
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == ',')
                ADVANCE(115);
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
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(118);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(94);
            LEX_ERROR();
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '.')
                ADVANCE(132);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '=')
                ADVANCE(125);
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
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '=')
                ADVANCE(125);
            LEX_ERROR();
        case 137:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '.')
                ADVANCE(132);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
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
                ADVANCE(118);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(123);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(118);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(123);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(123);
            if (lookahead == '=')
                ADVANCE(125);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(123);
            if (lookahead == '=')
                ADVANCE(125);
            if (lookahead == '[')
                ADVANCE(98);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(123);
            LEX_ERROR();
        case 143:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(81);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(143);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(118);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '.')
                ADVANCE(132);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
            if (lookahead == ';')
                ADVANCE(123);
            if (lookahead == '=')
                ADVANCE(125);
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
                ADVANCE(112);
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
                ADVANCE(143);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ')')
                ADVANCE(101);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(118);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '.')
                ADVANCE(132);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
            if (lookahead == ';')
                ADVANCE(123);
            if (lookahead == '=')
                ADVANCE(125);
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
                ADVANCE(112);
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
    [7] = 88,
    [8] = 1,
    [9] = 89,
    [10] = 91,
    [11] = 1,
    [12] = 85,
    [13] = 93,
    [14] = 95,
    [15] = 93,
    [16] = 85,
    [17] = 85,
    [18] = 93,
    [19] = 88,
    [20] = 96,
    [21] = 91,
    [22] = 85,
    [23] = 85,
    [24] = 93,
    [25] = 95,
    [26] = 93,
    [27] = 96,
    [28] = 85,
    [29] = 85,
    [30] = 96,
    [31] = 85,
    [32] = 85,
    [33] = 85,
    [34] = 96,
    [35] = 93,
    [36] = 97,
    [37] = 85,
    [38] = 99,
    [39] = 85,
    [40] = 85,
    [41] = 97,
    [42] = 100,
    [43] = 102,
    [44] = 99,
    [45] = 85,
    [46] = 102,
    [47] = 100,
    [48] = 102,
    [49] = 102,
    [50] = 103,
    [51] = 113,
    [52] = 82,
    [53] = 85,
    [54] = 114,
    [55] = 100,
    [56] = 1,
    [57] = 102,
    [58] = 114,
    [59] = 100,
    [60] = 102,
    [61] = 114,
    [62] = 116,
    [63] = 99,
    [64] = 85,
    [65] = 116,
    [66] = 100,
    [67] = 116,
    [68] = 116,
    [69] = 103,
    [70] = 113,
    [71] = 114,
    [72] = 100,
    [73] = 116,
    [74] = 116,
    [75] = 117,
    [76] = 117,
    [77] = 119,
    [78] = 120,
    [79] = 120,
    [80] = 117,
    [81] = 117,
    [82] = 121,
    [83] = 121,
    [84] = 117,
    [85] = 100,
    [86] = 120,
    [87] = 119,
    [88] = 117,
    [89] = 120,
    [90] = 120,
    [91] = 121,
    [92] = 121,
    [93] = 121,
    [94] = 121,
    [95] = 100,
    [96] = 121,
    [97] = 121,
    [98] = 121,
    [99] = 100,
    [100] = 117,
    [101] = 85,
    [102] = 114,
    [103] = 117,
    [104] = 97,
    [105] = 97,
    [106] = 103,
    [107] = 113,
    [108] = 114,
    [109] = 100,
    [110] = 97,
    [111] = 97,
    [112] = 117,
    [113] = 99,
    [114] = 96,
    [115] = 85,
    [116] = 88,
    [117] = 85,
    [118] = 122,
    [119] = 124,
    [120] = 126,
    [121] = 99,
    [122] = 85,
    [123] = 126,
    [124] = 100,
    [125] = 126,
    [126] = 126,
    [127] = 103,
    [128] = 113,
    [129] = 114,
    [130] = 100,
    [131] = 126,
    [132] = 126,
    [133] = 117,
    [134] = 82,
    [135] = 85,
    [136] = 127,
    [137] = 80,
    [138] = 95,
    [139] = 128,
    [140] = 129,
    [141] = 122,
    [142] = 130,
    [143] = 130,
    [144] = 131,
    [145] = 133,
    [146] = 133,
    [147] = 129,
    [148] = 134,
    [149] = 134,
    [150] = 131,
    [151] = 120,
    [152] = 88,
    [153] = 135,
    [154] = 136,
    [155] = 129,
    [156] = 120,
    [157] = 88,
    [158] = 135,
    [159] = 136,
    [160] = 117,
    [161] = 135,
    [162] = 136,
    [163] = 129,
    [164] = 117,
    [165] = 135,
    [166] = 136,
    [167] = 129,
    [168] = 133,
    [169] = 133,
    [170] = 137,
    [171] = 133,
    [172] = 129,
    [173] = 133,
    [174] = 133,
    [175] = 119,
    [176] = 120,
    [177] = 120,
    [178] = 134,
    [179] = 134,
    [180] = 121,
    [181] = 134,
    [182] = 100,
    [183] = 134,
    [184] = 134,
    [185] = 133,
    [186] = 122,
    [187] = 137,
    [188] = 122,
    [189] = 119,
    [190] = 120,
    [191] = 120,
    [192] = 130,
    [193] = 130,
    [194] = 121,
    [195] = 130,
    [196] = 100,
    [197] = 130,
    [198] = 130,
    [199] = 82,
    [200] = 85,
    [201] = 128,
    [202] = 138,
    [203] = 138,
    [204] = 128,
    [205] = 96,
    [206] = 80,
    [207] = 139,
    [208] = 80,
    [209] = 128,
    [210] = 119,
    [211] = 120,
    [212] = 120,
    [213] = 138,
    [214] = 138,
    [215] = 121,
    [216] = 138,
    [217] = 100,
    [218] = 138,
    [219] = 138,
    [220] = 96,
    [221] = 122,
    [222] = 140,
    [223] = 141,
    [224] = 99,
    [225] = 85,
    [226] = 141,
    [227] = 100,
    [228] = 141,
    [229] = 141,
    [230] = 103,
    [231] = 113,
    [232] = 114,
    [233] = 100,
    [234] = 141,
    [235] = 141,
    [236] = 117,
    [237] = 142,
    [238] = 85,
    [239] = 128,
    [240] = 122,
    [241] = 142,
    [242] = 128,
    [243] = 85,
    [244] = 122,
    [245] = 142,
    [246] = 128,
    [247] = 80,
    [248] = 95,
    [249] = 122,
    [250] = 142,
    [251] = 127,
    [252] = 127,
    [253] = 85,
    [254] = 122,
    [255] = 142,
    [256] = 127,
    [257] = 142,
    [258] = 80,
    [259] = 80,
    [260] = 1,
    [261] = 82,
    [262] = 82,
    [263] = 85,
    [264] = 122,
    [265] = 124,
    [266] = 95,
    [267] = 80,
    [268] = 142,
    [269] = 80,
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
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(12)),
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
        [sym__type_specifier] = ACTIONS(SHIFT(263)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(10)),
        [sym_identifier] = ACTIONS(SHIFT(12)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [4] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(260)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(260)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(261)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [5] = {
        [sym__init_declarator] = ACTIONS(SHIFT(118)),
        [sym_declarator] = ACTIONS(SHIFT(119)),
        [sym__direct_declarator] = ACTIONS(SHIFT(120)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(121)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(122)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(123)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [7] = {
        [sym_identifier] = ACTIONS(SHIFT(117)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(116)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [aux_sym_LBRACE] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(14)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [sym__type_specifier] = ACTIONS(SHIFT(16)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_struct_declaration] = ACTIONS(SHIFT(18)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(114)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RBRACE] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [aux_sym_LBRACE] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [15] = {
        [sym__type_specifier] = ACTIONS(SHIFT(16)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_struct_declaration] = ACTIONS(SHIFT(18)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(20)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RBRACE] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym_declarator] = ACTIONS(SHIFT(35)),
        [sym__direct_declarator] = ACTIONS(SHIFT(36)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(38)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(39)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [sym_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [sym__type_specifier] = ACTIONS(SHIFT(16)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_struct_declaration] = ACTIONS(SHIFT(18)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(34)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [sym_identifier] = ACTIONS(SHIFT(33)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [aux_sym_RBRACE] = ACTIONS(SHIFT(32)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [aux_sym_LBRACE] = ACTIONS(SHIFT(24)),
        [sym_identifier] = ACTIONS(SHIFT(25)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [sym__type_specifier] = ACTIONS(SHIFT(16)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_struct_declaration] = ACTIONS(SHIFT(18)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(30)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RBRACE] = ACTIONS(SHIFT(31)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [aux_sym_LBRACE] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [sym__type_specifier] = ACTIONS(SHIFT(16)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_struct_declaration] = ACTIONS(SHIFT(18)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(27)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RBRACE] = ACTIONS(SHIFT(28)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [aux_sym_RBRACE] = ACTIONS(SHIFT(29)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [aux_sym_RBRACE] = ACTIONS(SHIFT(28)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [33] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [34] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [35] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [36] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(106)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(107)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [37] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(113)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [38] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(105)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(39)),
        [sym_identifier] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [39] = {
        [sym_declarator] = ACTIONS(SHIFT(42)),
        [sym__direct_declarator] = ACTIONS(SHIFT(43)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [40] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_pointer, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [41] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [42] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(104)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [43] = {
        [aux_sym_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(51)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [44] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(49)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(45)),
        [sym_identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [45] = {
        [sym_declarator] = ACTIONS(SHIFT(47)),
        [sym__direct_declarator] = ACTIONS(SHIFT(43)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [46] = {
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [47] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(48)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [48] = {
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [49] = {
        [aux_sym_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(51)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [50] = {
        [sym_expression] = ACTIONS(SHIFT(103)),
        [sym_math_expression] = ACTIONS(SHIFT(76)),
        [sym_call_expression] = ACTIONS(SHIFT(76)),
        [aux_sym_RBRACK] = ACTIONS(SHIFT(48)),
        [sym_string] = ACTIONS(SHIFT(76)),
        [sym_identifier] = ACTIONS(SHIFT(76)),
        [sym_number] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [51] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(52)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(53)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(54)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(48)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [52] = {
        [sym__type_specifier] = ACTIONS(SHIFT(101)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [53] = {
        [sym_declarator] = ACTIONS(SHIFT(61)),
        [sym__direct_declarator] = ACTIONS(SHIFT(62)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(63)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(64)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [54] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(55)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(56)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(57)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [55] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(60)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [56] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(52)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(53)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(58)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [57] = {
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [58] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(59)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(56)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__direct_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [59] = {
        [aux_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__direct_declarator_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [60] = {
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [61] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [62] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(69)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [63] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(68)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(64)),
        [sym_identifier] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [64] = {
        [sym_declarator] = ACTIONS(SHIFT(66)),
        [sym__direct_declarator] = ACTIONS(SHIFT(43)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [65] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [66] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(67)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [67] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [68] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(69)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [69] = {
        [sym_expression] = ACTIONS(SHIFT(75)),
        [sym_math_expression] = ACTIONS(SHIFT(76)),
        [sym_call_expression] = ACTIONS(SHIFT(76)),
        [aux_sym_RBRACK] = ACTIONS(SHIFT(67)),
        [sym_string] = ACTIONS(SHIFT(76)),
        [sym_identifier] = ACTIONS(SHIFT(76)),
        [sym_number] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [70] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(52)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(53)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(71)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(67)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [71] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(72)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(56)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [72] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(74)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [75] = {
        [aux_sym_RBRACK] = ACTIONS(SHIFT(73)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(77)),
        [aux_sym_STAR] = ACTIONS(SHIFT(78)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [aux_sym_RBRACK] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [sym_expression] = ACTIONS(SHIFT(82)),
        [sym_math_expression] = ACTIONS(SHIFT(83)),
        [sym_call_expression] = ACTIONS(SHIFT(83)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(83)),
        [sym_identifier] = ACTIONS(SHIFT(83)),
        [sym_number] = ACTIONS(SHIFT(83)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [sym_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(76)),
        [sym_call_expression] = ACTIONS(SHIFT(76)),
        [sym_string] = ACTIONS(SHIFT(76)),
        [sym_identifier] = ACTIONS(SHIFT(76)),
        [sym_number] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [sym_expression] = ACTIONS(SHIFT(80)),
        [sym_math_expression] = ACTIONS(SHIFT(76)),
        [sym_call_expression] = ACTIONS(SHIFT(76)),
        [sym_string] = ACTIONS(SHIFT(76)),
        [sym_identifier] = ACTIONS(SHIFT(76)),
        [sym_number] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [80] = {
        [aux_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(77)),
        [aux_sym_STAR] = ACTIONS(SHIFT(78)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [aux_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(77)),
        [aux_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [82] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(85)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(86)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(88)),
        [aux_sym_STAR] = ACTIONS(SHIFT(89)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(90)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [aux_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(100)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [sym_expression] = ACTIONS(SHIFT(98)),
        [sym_math_expression] = ACTIONS(SHIFT(83)),
        [sym_call_expression] = ACTIONS(SHIFT(83)),
        [sym_string] = ACTIONS(SHIFT(83)),
        [sym_identifier] = ACTIONS(SHIFT(83)),
        [sym_number] = ACTIONS(SHIFT(83)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [sym_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(83)),
        [sym_call_expression] = ACTIONS(SHIFT(83)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(94)),
        [sym_string] = ACTIONS(SHIFT(83)),
        [sym_identifier] = ACTIONS(SHIFT(83)),
        [sym_number] = ACTIONS(SHIFT(83)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [aux_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [sym_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(83)),
        [sym_call_expression] = ACTIONS(SHIFT(83)),
        [sym_string] = ACTIONS(SHIFT(83)),
        [sym_identifier] = ACTIONS(SHIFT(83)),
        [sym_number] = ACTIONS(SHIFT(83)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [sym_expression] = ACTIONS(SHIFT(91)),
        [sym_math_expression] = ACTIONS(SHIFT(83)),
        [sym_call_expression] = ACTIONS(SHIFT(83)),
        [sym_string] = ACTIONS(SHIFT(83)),
        [sym_identifier] = ACTIONS(SHIFT(83)),
        [sym_number] = ACTIONS(SHIFT(83)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STAR] = ACTIONS(SHIFT(89)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(95)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(86)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(96)),
        [aux_sym_STAR] = ACTIONS(SHIFT(89)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(90)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(97)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(99)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(86)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [aux_sym_STAR] = ACTIONS(SHIFT(89)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(90)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [99] = {
        [aux_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [aux_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [sym_declarator] = ACTIONS(SHIFT(102)),
        [sym__direct_declarator] = ACTIONS(SHIFT(62)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(63)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(64)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [103] = {
        [aux_sym_RBRACK] = ACTIONS(SHIFT(57)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(77)),
        [aux_sym_STAR] = ACTIONS(SHIFT(78)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(106)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(107)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [106] = {
        [sym_expression] = ACTIONS(SHIFT(112)),
        [sym_math_expression] = ACTIONS(SHIFT(76)),
        [sym_call_expression] = ACTIONS(SHIFT(76)),
        [aux_sym_RBRACK] = ACTIONS(SHIFT(104)),
        [sym_string] = ACTIONS(SHIFT(76)),
        [sym_identifier] = ACTIONS(SHIFT(76)),
        [sym_number] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [107] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(52)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(53)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(108)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(104)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [108] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(109)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(56)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(110)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(111)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [aux_sym_RBRACK] = ACTIONS(SHIFT(110)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(77)),
        [aux_sym_STAR] = ACTIONS(SHIFT(78)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [aux_sym_RBRACE] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [116] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [117] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(257)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_SEMI] = ACTIONS(SHIFT(258)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [119] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(134)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(135)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(136)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(137)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(138)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(139)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_EQ] = ACTIONS(SHIFT(140)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(12)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [120] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(127)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(128)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [121] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(126)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(122)),
        [sym_identifier] = ACTIONS(SHIFT(123)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [122] = {
        [sym_declarator] = ACTIONS(SHIFT(124)),
        [sym__direct_declarator] = ACTIONS(SHIFT(43)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [123] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_static] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_register] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_const] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [124] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [125] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_static] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_register] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_const] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(127)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(128)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
        [sym_expression] = ACTIONS(SHIFT(133)),
        [sym_math_expression] = ACTIONS(SHIFT(76)),
        [sym_call_expression] = ACTIONS(SHIFT(76)),
        [aux_sym_RBRACK] = ACTIONS(SHIFT(125)),
        [sym_string] = ACTIONS(SHIFT(76)),
        [sym_identifier] = ACTIONS(SHIFT(76)),
        [sym_number] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(52)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(53)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(129)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(125)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(130)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(56)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(131)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(132)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [131] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_static] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_register] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_const] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_static] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_register] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_long] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_short] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_const] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [133] = {
        [aux_sym_RBRACK] = ACTIONS(SHIFT(131)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(77)),
        [aux_sym_STAR] = ACTIONS(SHIFT(78)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [sym__type_specifier] = ACTIONS(SHIFT(253)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(10)),
        [sym_identifier] = ACTIONS(SHIFT(12)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [sym__init_declarator] = ACTIONS(SHIFT(249)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(224)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(225)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(226)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(134)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(135)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(136)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(248)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(12)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [sym_compound_statement] = ACTIONS(SHIFT(247)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(139)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [139] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(199)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(200)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(201)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(202)),
        [sym_math_expression] = ACTIONS(SHIFT(203)),
        [sym_call_expression] = ACTIONS(SHIFT(203)),
        [sym_statement] = ACTIONS(SHIFT(201)),
        [sym_expression_statement] = ACTIONS(SHIFT(204)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(205)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_RBRACE] = ACTIONS(SHIFT(206)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_string] = ACTIONS(SHIFT(203)),
        [sym_identifier] = ACTIONS(SHIFT(207)),
        [sym_number] = ACTIONS(SHIFT(203)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [140] = {
        [sym_initializer] = ACTIONS(SHIFT(141)),
        [sym_expression] = ACTIONS(SHIFT(142)),
        [sym_math_expression] = ACTIONS(SHIFT(143)),
        [sym_call_expression] = ACTIONS(SHIFT(143)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(144)),
        [sym_string] = ACTIONS(SHIFT(143)),
        [sym_identifier] = ACTIONS(SHIFT(143)),
        [sym_number] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(189)),
        [aux_sym_STAR] = ACTIONS(SHIFT(190)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(191)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [144] = {
        [sym_initializer] = ACTIONS(SHIFT(145)),
        [sym_initializer_list] = ACTIONS(SHIFT(146)),
        [sym_designation] = ACTIONS(SHIFT(147)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(150)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(151)),
        [aux_sym_DOT] = ACTIONS(SHIFT(152)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [145] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [aux_sym_RBRACE] = ACTIONS(SHIFT(186)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(187)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [sym_initializer] = ACTIONS(SHIFT(185)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(150)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(175)),
        [aux_sym_STAR] = ACTIONS(SHIFT(176)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(177)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [sym_initializer] = ACTIONS(SHIFT(145)),
        [sym_initializer_list] = ACTIONS(SHIFT(168)),
        [sym_designation] = ACTIONS(SHIFT(147)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(150)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(151)),
        [aux_sym_DOT] = ACTIONS(SHIFT(152)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [sym_expression] = ACTIONS(SHIFT(164)),
        [sym_math_expression] = ACTIONS(SHIFT(76)),
        [sym_call_expression] = ACTIONS(SHIFT(76)),
        [sym_string] = ACTIONS(SHIFT(76)),
        [sym_identifier] = ACTIONS(SHIFT(76)),
        [sym_number] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [sym_identifier] = ACTIONS(SHIFT(153)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(154)),
        [aux_sym_EQ] = ACTIONS(SHIFT(155)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(156)),
        [aux_sym_DOT] = ACTIONS(SHIFT(157)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [aux_sym_EQ] = ACTIONS(SHIFT(163)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 3)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [sym_expression] = ACTIONS(SHIFT(160)),
        [sym_math_expression] = ACTIONS(SHIFT(76)),
        [sym_call_expression] = ACTIONS(SHIFT(76)),
        [sym_string] = ACTIONS(SHIFT(76)),
        [sym_identifier] = ACTIONS(SHIFT(76)),
        [sym_number] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [sym_identifier] = ACTIONS(SHIFT(158)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(159)),
        [aux_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(156)),
        [aux_sym_DOT] = ACTIONS(SHIFT(157)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [aux_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [aux_sym_RBRACK] = ACTIONS(SHIFT(161)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(77)),
        [aux_sym_STAR] = ACTIONS(SHIFT(78)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(162)),
        [aux_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(156)),
        [aux_sym_DOT] = ACTIONS(SHIFT(157)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [aux_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 4)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [aux_sym_RBRACK] = ACTIONS(SHIFT(165)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(77)),
        [aux_sym_STAR] = ACTIONS(SHIFT(78)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(166)),
        [aux_sym_EQ] = ACTIONS(SHIFT(163)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(156)),
        [aux_sym_DOT] = ACTIONS(SHIFT(157)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [aux_sym_EQ] = ACTIONS(SHIFT(167)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 5)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [aux_sym_RBRACE] = ACTIONS(SHIFT(169)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [sym_initializer] = ACTIONS(SHIFT(171)),
        [sym_designation] = ACTIONS(SHIFT(172)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(150)),
        [aux_sym_RBRACE] = ACTIONS(SHIFT(173)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(151)),
        [aux_sym_DOT] = ACTIONS(SHIFT(152)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [172] = {
        [sym_initializer] = ACTIONS(SHIFT(174)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(150)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [sym_expression] = ACTIONS(SHIFT(180)),
        [sym_math_expression] = ACTIONS(SHIFT(83)),
        [sym_call_expression] = ACTIONS(SHIFT(83)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(181)),
        [sym_string] = ACTIONS(SHIFT(83)),
        [sym_identifier] = ACTIONS(SHIFT(83)),
        [sym_number] = ACTIONS(SHIFT(83)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [sym_expression] = ACTIONS(SHIFT(179)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [sym_expression] = ACTIONS(SHIFT(178)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(175)),
        [aux_sym_STAR] = ACTIONS(SHIFT(176)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(175)),
        [aux_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [180] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(182)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(86)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(183)),
        [aux_sym_STAR] = ACTIONS(SHIFT(89)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(90)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(184)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [185] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [186] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [sym_initializer] = ACTIONS(SHIFT(171)),
        [sym_designation] = ACTIONS(SHIFT(172)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(150)),
        [aux_sym_RBRACE] = ACTIONS(SHIFT(188)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(151)),
        [aux_sym_DOT] = ACTIONS(SHIFT(152)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [188] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [sym_expression] = ACTIONS(SHIFT(194)),
        [sym_math_expression] = ACTIONS(SHIFT(83)),
        [sym_call_expression] = ACTIONS(SHIFT(83)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(195)),
        [sym_string] = ACTIONS(SHIFT(83)),
        [sym_identifier] = ACTIONS(SHIFT(83)),
        [sym_number] = ACTIONS(SHIFT(83)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [sym_expression] = ACTIONS(SHIFT(193)),
        [sym_math_expression] = ACTIONS(SHIFT(143)),
        [sym_call_expression] = ACTIONS(SHIFT(143)),
        [sym_string] = ACTIONS(SHIFT(143)),
        [sym_identifier] = ACTIONS(SHIFT(143)),
        [sym_number] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [sym_expression] = ACTIONS(SHIFT(192)),
        [sym_math_expression] = ACTIONS(SHIFT(143)),
        [sym_call_expression] = ACTIONS(SHIFT(143)),
        [sym_string] = ACTIONS(SHIFT(143)),
        [sym_identifier] = ACTIONS(SHIFT(143)),
        [sym_number] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(189)),
        [aux_sym_STAR] = ACTIONS(SHIFT(190)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(189)),
        [aux_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(196)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(86)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(197)),
        [aux_sym_STAR] = ACTIONS(SHIFT(89)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(90)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(198)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [sym__type_specifier] = ACTIONS(SHIFT(243)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(10)),
        [sym_identifier] = ACTIONS(SHIFT(12)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [sym__init_declarator] = ACTIONS(SHIFT(221)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(224)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(225)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(226)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(199)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(200)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(201)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(202)),
        [sym_math_expression] = ACTIONS(SHIFT(203)),
        [sym_call_expression] = ACTIONS(SHIFT(203)),
        [sym_statement] = ACTIONS(SHIFT(201)),
        [sym_expression_statement] = ACTIONS(SHIFT(204)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(220)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_string] = ACTIONS(SHIFT(203)),
        [sym_identifier] = ACTIONS(SHIFT(207)),
        [sym_number] = ACTIONS(SHIFT(203)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [aux_sym_SEMI] = ACTIONS(SHIFT(209)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(210)),
        [aux_sym_STAR] = ACTIONS(SHIFT(211)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(212)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
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
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_string] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [aux_sym_RBRACE] = ACTIONS(SHIFT(208)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1), REDUCE(sym_expression, 1)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 1), REDUCE(sym_expression, 1)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [209] = {
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
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [sym_expression] = ACTIONS(SHIFT(215)),
        [sym_math_expression] = ACTIONS(SHIFT(83)),
        [sym_call_expression] = ACTIONS(SHIFT(83)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(216)),
        [sym_string] = ACTIONS(SHIFT(83)),
        [sym_identifier] = ACTIONS(SHIFT(83)),
        [sym_number] = ACTIONS(SHIFT(83)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [sym_expression] = ACTIONS(SHIFT(214)),
        [sym_math_expression] = ACTIONS(SHIFT(203)),
        [sym_call_expression] = ACTIONS(SHIFT(203)),
        [sym_string] = ACTIONS(SHIFT(203)),
        [sym_identifier] = ACTIONS(SHIFT(203)),
        [sym_number] = ACTIONS(SHIFT(203)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
        [sym_expression] = ACTIONS(SHIFT(213)),
        [sym_math_expression] = ACTIONS(SHIFT(203)),
        [sym_call_expression] = ACTIONS(SHIFT(203)),
        [sym_string] = ACTIONS(SHIFT(203)),
        [sym_identifier] = ACTIONS(SHIFT(203)),
        [sym_number] = ACTIONS(SHIFT(203)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [213] = {
        [aux_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(210)),
        [aux_sym_STAR] = ACTIONS(SHIFT(211)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [aux_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(210)),
        [aux_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(217)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(86)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(218)),
        [aux_sym_STAR] = ACTIONS(SHIFT(89)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(90)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(219)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [219] = {
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
        [aux_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(237)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_SEMI] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_EQ] = ACTIONS(SHIFT(140)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(230)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(231)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(229)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(225)),
        [sym_identifier] = ACTIONS(SHIFT(226)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [225] = {
        [sym_declarator] = ACTIONS(SHIFT(227)),
        [sym__direct_declarator] = ACTIONS(SHIFT(43)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(228)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [228] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_LBRACK] = ACTIONS(SHIFT(230)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(231)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
        [sym_expression] = ACTIONS(SHIFT(236)),
        [sym_math_expression] = ACTIONS(SHIFT(76)),
        [sym_call_expression] = ACTIONS(SHIFT(76)),
        [aux_sym_RBRACK] = ACTIONS(SHIFT(228)),
        [sym_string] = ACTIONS(SHIFT(76)),
        [sym_identifier] = ACTIONS(SHIFT(76)),
        [sym_number] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [231] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(52)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(53)),
        [sym_type_name] = ACTIONS(SHIFT(17)),
        [sym_struct_specifier] = ACTIONS(SHIFT(17)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(232)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(228)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(233)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(56)),
        [aux_sym_RPAREN] = ACTIONS(SHIFT(234)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [233] = {
        [aux_sym_RPAREN] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
        [aux_sym_RBRACK] = ACTIONS(SHIFT(234)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(77)),
        [aux_sym_STAR] = ACTIONS(SHIFT(78)),
        [aux_sym_PLUS] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [237] = {
        [aux_sym_SEMI] = ACTIONS(SHIFT(242)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [238] = {
        [sym__init_declarator] = ACTIONS(SHIFT(240)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(224)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(225)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(226)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
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
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [240] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(241)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [241] = {
        [aux_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
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
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [243] = {
        [sym__init_declarator] = ACTIONS(SHIFT(244)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(224)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(225)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(226)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(245)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_SEMI] = ACTIONS(SHIFT(242)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
        [aux_sym_SEMI] = ACTIONS(SHIFT(246)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [246] = {
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
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [247] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(250)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_SEMI] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [250] = {
        [aux_sym_SEMI] = ACTIONS(SHIFT(252)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [sym__init_declarator] = ACTIONS(SHIFT(254)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(224)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(225)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(226)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(255)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_SEMI] = ACTIONS(SHIFT(252)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
        [aux_sym_SEMI] = ACTIONS(SHIFT(256)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_extern] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_static] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_auto] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_register] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_const] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [aux_sym_SEMI] = ACTIONS(SHIFT(259)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [259] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [260] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(260)),
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_name] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(260)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(262)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [261] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_signed] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_long] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_short] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_struct] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [262] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_type_name] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
        [sym__init_declarator] = ACTIONS(SHIFT(264)),
        [sym_declarator] = ACTIONS(SHIFT(265)),
        [sym__direct_declarator] = ACTIONS(SHIFT(120)),
        [sym_pointer] = ACTIONS(SHIFT(37)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(121)),
        [aux_sym_LPAREN] = ACTIONS(SHIFT(122)),
        [aux_sym_STAR] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(123)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [264] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(268)),
        [aux_sym_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_SEMI] = ACTIONS(SHIFT(259)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [265] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(134)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(135)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(136)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(247)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(266)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_static] = ACTIONS(SHIFT(8)),
        [aux_sym_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_register] = ACTIONS(SHIFT(8)),
        [aux_sym_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_long] = ACTIONS(SHIFT(9)),
        [aux_sym_short] = ACTIONS(SHIFT(9)),
        [aux_sym_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(139)),
        [aux_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_EQ] = ACTIONS(SHIFT(140)),
        [aux_sym_const] = ACTIONS(SHIFT(11)),
        [aux_sym_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_volatile] = ACTIONS(SHIFT(11)),
        [sym_identifier] = ACTIONS(SHIFT(12)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [sym_compound_statement] = ACTIONS(SHIFT(267)),
        [aux_sym_LBRACE] = ACTIONS(SHIFT(139)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [267] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [268] = {
        [aux_sym_SEMI] = ACTIONS(SHIFT(269)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [269] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
