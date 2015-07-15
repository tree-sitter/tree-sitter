#include "tree_sitter/parser.h"

#define STATE_COUNT 267
#define SYMBOL_COUNT 64

enum {
    sym_program = ts_builtin_sym_start,
    sym_function_definition,
    sym_declaration_specifiers,
    sym_storage_class_specifier,
    sym_type_specifier,
    sym_struct_specifier,
    sym_struct_declaration,
    sym_parameter_declaration,
    sym_declaration,
    sym_init_declarator,
    sym_initializer,
    sym_initializer_list,
    sym_designation,
    sym_declarator,
    sym_direct_declarator,
    sym_type_qualifier,
    sym_compound_statement,
    sym_expression,
    sym_math_expression,
    sym_call_expression,
    sym_statement,
    sym_expression_statement,
    sym_star,
    sym_string,
    sym_identifier,
    sym_number,
    sym_comment,
    aux_sym_function_definition_repeat1,
    aux_sym_declaration_specifiers_repeat1,
    aux_sym_type_specifier_repeat1,
    aux_sym_struct_specifier_repeat1,
    aux_sym_declaration_repeat1,
    aux_sym_designation_repeat1,
    aux_sym_declarator_repeat1,
    aux_sym_direct_declarator_repeat1,
    aux_sym_compound_statement_repeat1,
    aux_sym_call_expression_repeat1,
    aux_sym_STR_typedef,
    aux_sym_STR_extern,
    aux_sym_STR_static,
    aux_sym_STR_auto,
    aux_sym_STR_register,
    aux_sym_STR_signed,
    aux_sym_STR_unsigned,
    aux_sym_STR_long,
    aux_sym_STR_short,
    aux_sym_STR_struct,
    aux_sym_STR_LBRACE,
    aux_sym_STR_RBRACE,
    aux_sym_STR_COMMA,
    aux_sym_STR_SEMI,
    aux_sym_STR_EQ,
    aux_sym_STR_LBRACK,
    aux_sym_STR_RBRACK,
    aux_sym_STR_DOT,
    aux_sym_STR_LPAREN,
    aux_sym_STR_RPAREN,
    aux_sym_STR_const,
    aux_sym_STR_restrict,
    aux_sym_STR_volatile,
    aux_sym_STR_PLUS,
};

static const char *ts_symbol_names[] = {
    [ts_builtin_sym_document] = "DOCUMENT",
    [sym_program] = "program",
    [sym_function_definition] = "function_definition",
    [sym_declaration_specifiers] = "declaration_specifiers",
    [sym_storage_class_specifier] = "storage_class_specifier",
    [sym_type_specifier] = "type_specifier",
    [sym_struct_specifier] = "struct_specifier",
    [sym_struct_declaration] = "struct_declaration",
    [sym_parameter_declaration] = "parameter_declaration",
    [sym_declaration] = "declaration",
    [sym_init_declarator] = "init_declarator",
    [sym_initializer] = "initializer",
    [sym_initializer_list] = "initializer_list",
    [sym_designation] = "designation",
    [sym_declarator] = "declarator",
    [sym_direct_declarator] = "direct_declarator",
    [sym_type_qualifier] = "type_qualifier",
    [sym_compound_statement] = "compound_statement",
    [sym_expression] = "expression",
    [sym_math_expression] = "math_expression",
    [sym_call_expression] = "call_expression",
    [sym_statement] = "statement",
    [sym_expression_statement] = "expression_statement",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
    [sym_star] = "star",
    [sym_string] = "string",
    [sym_identifier] = "identifier",
    [sym_number] = "number",
    [sym_comment] = "comment",
    [aux_sym_function_definition_repeat1] = "function_definition_repeat1",
    [aux_sym_declaration_specifiers_repeat1] = "declaration_specifiers_repeat1",
    [aux_sym_type_specifier_repeat1] = "type_specifier_repeat1",
    [aux_sym_struct_specifier_repeat1] = "struct_specifier_repeat1",
    [aux_sym_declaration_repeat1] = "declaration_repeat1",
    [aux_sym_designation_repeat1] = "designation_repeat1",
    [aux_sym_declarator_repeat1] = "declarator_repeat1",
    [aux_sym_direct_declarator_repeat1] = "direct_declarator_repeat1",
    [aux_sym_compound_statement_repeat1] = "compound_statement_repeat1",
    [aux_sym_call_expression_repeat1] = "call_expression_repeat1",
    [aux_sym_STR_typedef] = "STR_typedef",
    [aux_sym_STR_extern] = "STR_extern",
    [aux_sym_STR_static] = "STR_static",
    [aux_sym_STR_auto] = "STR_auto",
    [aux_sym_STR_register] = "STR_register",
    [aux_sym_STR_signed] = "STR_signed",
    [aux_sym_STR_unsigned] = "STR_unsigned",
    [aux_sym_STR_long] = "STR_long",
    [aux_sym_STR_short] = "STR_short",
    [aux_sym_STR_struct] = "STR_struct",
    [aux_sym_STR_LBRACE] = "STR_{",
    [aux_sym_STR_RBRACE] = "STR_}",
    [aux_sym_STR_COMMA] = "STR_,",
    [aux_sym_STR_SEMI] = "STR_;",
    [aux_sym_STR_EQ] = "STR_=",
    [aux_sym_STR_LBRACK] = "STR_[",
    [aux_sym_STR_RBRACK] = "STR_]",
    [aux_sym_STR_DOT] = "STR_.",
    [aux_sym_STR_LPAREN] = "STR_(",
    [aux_sym_STR_RPAREN] = "STR_)",
    [aux_sym_STR_const] = "STR_const",
    [aux_sym_STR_restrict] = "STR_restrict",
    [aux_sym_STR_volatile] = "STR_volatile",
    [aux_sym_STR_PLUS] = "STR_+",
};

static const int ts_hidden_symbol_flags[SYMBOL_COUNT] = {
    [aux_sym_function_definition_repeat1] = 1,
    [aux_sym_declaration_specifiers_repeat1] = 1,
    [aux_sym_type_specifier_repeat1] = 1,
    [aux_sym_struct_specifier_repeat1] = 1,
    [aux_sym_declaration_repeat1] = 1,
    [aux_sym_designation_repeat1] = 1,
    [aux_sym_declarator_repeat1] = 1,
    [aux_sym_direct_declarator_repeat1] = 1,
    [aux_sym_compound_statement_repeat1] = 1,
    [aux_sym_call_expression_repeat1] = 1,
    [aux_sym_STR_typedef] = 1,
    [aux_sym_STR_extern] = 1,
    [aux_sym_STR_static] = 1,
    [aux_sym_STR_auto] = 1,
    [aux_sym_STR_register] = 1,
    [aux_sym_STR_signed] = 1,
    [aux_sym_STR_unsigned] = 1,
    [aux_sym_STR_long] = 1,
    [aux_sym_STR_short] = 1,
    [aux_sym_STR_struct] = 1,
    [aux_sym_STR_LBRACE] = 1,
    [aux_sym_STR_RBRACE] = 1,
    [aux_sym_STR_COMMA] = 1,
    [aux_sym_STR_SEMI] = 1,
    [aux_sym_STR_EQ] = 1,
    [aux_sym_STR_LBRACK] = 1,
    [aux_sym_STR_RBRACK] = 1,
    [aux_sym_STR_DOT] = 1,
    [aux_sym_STR_LPAREN] = 1,
    [aux_sym_STR_RPAREN] = 1,
    [aux_sym_STR_const] = 1,
    [aux_sym_STR_restrict] = 1,
    [aux_sym_STR_volatile] = 1,
    [aux_sym_STR_PLUS] = 1,
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
            ACCEPT_TOKEN(aux_sym_STR_auto);
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
            ACCEPT_TOKEN(aux_sym_STR_const);
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
            ACCEPT_TOKEN(aux_sym_STR_extern);
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
            ACCEPT_TOKEN(aux_sym_STR_long);
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
            ACCEPT_TOKEN(aux_sym_STR_register);
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
            ACCEPT_TOKEN(aux_sym_STR_restrict);
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
            ACCEPT_TOKEN(aux_sym_STR_short);
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
            ACCEPT_TOKEN(aux_sym_STR_signed);
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
            ACCEPT_TOKEN(aux_sym_STR_static);
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
            ACCEPT_TOKEN(aux_sym_STR_struct);
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
            ACCEPT_TOKEN(aux_sym_STR_typedef);
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
            ACCEPT_TOKEN(aux_sym_STR_unsigned);
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
            ACCEPT_TOKEN(aux_sym_STR_volatile);
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
            ACCEPT_TOKEN(aux_sym_STR_LPAREN);
        case 87:
            ACCEPT_TOKEN(sym_star);
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
            ACCEPT_TOKEN(aux_sym_STR_LBRACE);
        case 93:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(93);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 94:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(94);
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
                ADVANCE(95);
            LEX_ERROR();
        case 95:
            ACCEPT_TOKEN(aux_sym_STR_RBRACE);
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
                ADVANCE(95);
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
                ADVANCE(95);
            LEX_ERROR();
        case 98:
            ACCEPT_TOKEN(aux_sym_STR_LBRACK);
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
            ACCEPT_TOKEN(aux_sym_STR_RPAREN);
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
            ACCEPT_TOKEN(aux_sym_STR_RBRACK);
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
            ACCEPT_TOKEN(aux_sym_STR_COMMA);
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
            ACCEPT_TOKEN(aux_sym_STR_PLUS);
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
            ACCEPT_TOKEN(aux_sym_STR_SEMI);
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
            ACCEPT_TOKEN(aux_sym_STR_EQ);
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
                ADVANCE(95);
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
            ACCEPT_TOKEN(aux_sym_STR_DOT);
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
                ADVANCE(95);
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
                ADVANCE(95);
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
                ADVANCE(95);
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
                ADVANCE(95);
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
                ADVANCE(95);
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
    [12] = 93,
    [13] = 94,
    [14] = 85,
    [15] = 85,
    [16] = 94,
    [17] = 88,
    [18] = 96,
    [19] = 91,
    [20] = 85,
    [21] = 93,
    [22] = 94,
    [23] = 96,
    [24] = 85,
    [25] = 85,
    [26] = 94,
    [27] = 96,
    [28] = 85,
    [29] = 85,
    [30] = 85,
    [31] = 96,
    [32] = 94,
    [33] = 97,
    [34] = 85,
    [35] = 97,
    [36] = 99,
    [37] = 85,
    [38] = 100,
    [39] = 102,
    [40] = 102,
    [41] = 99,
    [42] = 85,
    [43] = 100,
    [44] = 102,
    [45] = 102,
    [46] = 103,
    [47] = 113,
    [48] = 82,
    [49] = 85,
    [50] = 114,
    [51] = 100,
    [52] = 1,
    [53] = 102,
    [54] = 114,
    [55] = 100,
    [56] = 102,
    [57] = 114,
    [58] = 116,
    [59] = 116,
    [60] = 99,
    [61] = 85,
    [62] = 100,
    [63] = 116,
    [64] = 116,
    [65] = 103,
    [66] = 113,
    [67] = 114,
    [68] = 100,
    [69] = 116,
    [70] = 116,
    [71] = 117,
    [72] = 117,
    [73] = 119,
    [74] = 120,
    [75] = 119,
    [76] = 117,
    [77] = 121,
    [78] = 121,
    [79] = 117,
    [80] = 119,
    [81] = 100,
    [82] = 119,
    [83] = 120,
    [84] = 117,
    [85] = 119,
    [86] = 121,
    [87] = 121,
    [88] = 121,
    [89] = 100,
    [90] = 121,
    [91] = 121,
    [92] = 121,
    [93] = 100,
    [94] = 117,
    [95] = 121,
    [96] = 117,
    [97] = 85,
    [98] = 114,
    [99] = 117,
    [100] = 97,
    [101] = 97,
    [102] = 103,
    [103] = 113,
    [104] = 114,
    [105] = 100,
    [106] = 97,
    [107] = 97,
    [108] = 117,
    [109] = 99,
    [110] = 94,
    [111] = 96,
    [112] = 85,
    [113] = 88,
    [114] = 85,
    [115] = 122,
    [116] = 124,
    [117] = 126,
    [118] = 126,
    [119] = 99,
    [120] = 85,
    [121] = 100,
    [122] = 126,
    [123] = 126,
    [124] = 103,
    [125] = 113,
    [126] = 114,
    [127] = 100,
    [128] = 126,
    [129] = 126,
    [130] = 117,
    [131] = 82,
    [132] = 85,
    [133] = 127,
    [134] = 80,
    [135] = 93,
    [136] = 128,
    [137] = 129,
    [138] = 122,
    [139] = 130,
    [140] = 130,
    [141] = 131,
    [142] = 133,
    [143] = 133,
    [144] = 129,
    [145] = 134,
    [146] = 134,
    [147] = 131,
    [148] = 119,
    [149] = 88,
    [150] = 135,
    [151] = 136,
    [152] = 129,
    [153] = 119,
    [154] = 88,
    [155] = 135,
    [156] = 136,
    [157] = 117,
    [158] = 135,
    [159] = 136,
    [160] = 129,
    [161] = 117,
    [162] = 135,
    [163] = 136,
    [164] = 129,
    [165] = 133,
    [166] = 133,
    [167] = 137,
    [168] = 133,
    [169] = 129,
    [170] = 133,
    [171] = 133,
    [172] = 119,
    [173] = 120,
    [174] = 119,
    [175] = 134,
    [176] = 121,
    [177] = 134,
    [178] = 100,
    [179] = 134,
    [180] = 134,
    [181] = 134,
    [182] = 133,
    [183] = 122,
    [184] = 137,
    [185] = 122,
    [186] = 119,
    [187] = 120,
    [188] = 119,
    [189] = 130,
    [190] = 121,
    [191] = 130,
    [192] = 100,
    [193] = 130,
    [194] = 130,
    [195] = 130,
    [196] = 82,
    [197] = 85,
    [198] = 128,
    [199] = 138,
    [200] = 138,
    [201] = 128,
    [202] = 139,
    [203] = 96,
    [204] = 80,
    [205] = 80,
    [206] = 119,
    [207] = 128,
    [208] = 120,
    [209] = 119,
    [210] = 138,
    [211] = 121,
    [212] = 138,
    [213] = 100,
    [214] = 138,
    [215] = 138,
    [216] = 138,
    [217] = 96,
    [218] = 122,
    [219] = 140,
    [220] = 141,
    [221] = 141,
    [222] = 99,
    [223] = 85,
    [224] = 100,
    [225] = 141,
    [226] = 141,
    [227] = 103,
    [228] = 113,
    [229] = 114,
    [230] = 100,
    [231] = 141,
    [232] = 141,
    [233] = 117,
    [234] = 142,
    [235] = 85,
    [236] = 128,
    [237] = 122,
    [238] = 142,
    [239] = 128,
    [240] = 85,
    [241] = 122,
    [242] = 142,
    [243] = 128,
    [244] = 80,
    [245] = 93,
    [246] = 122,
    [247] = 142,
    [248] = 127,
    [249] = 127,
    [250] = 85,
    [251] = 122,
    [252] = 142,
    [253] = 127,
    [254] = 142,
    [255] = 80,
    [256] = 80,
    [257] = 1,
    [258] = 82,
    [259] = 82,
    [260] = 85,
    [261] = 122,
    [262] = 124,
    [263] = 93,
    [264] = 80,
    [265] = 142,
    [266] = 80,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction *ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = ACTIONS(SHIFT(1)),
        [sym_function_definition] = ACTIONS(SHIFT(2)),
        [sym_declaration_specifiers] = ACTIONS(SHIFT(3)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(5)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(2)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
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
        [sym_type_specifier] = ACTIONS(SHIFT(260)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(10)),
    },
    [4] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(257)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(257)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(258)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [5] = {
        [sym_init_declarator] = ACTIONS(SHIFT(115)),
        [sym_declarator] = ACTIONS(SHIFT(116)),
        [sym_direct_declarator] = ACTIONS(SHIFT(117)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(118)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(119)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(120)),
    },
    [6] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_star] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1)),
    },
    [7] = {
        [sym_identifier] = ACTIONS(SHIFT(114)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
    },
    [9] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_specifier_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(113)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
    },
    [10] = {
        [sym_identifier] = ACTIONS(SHIFT(12)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(13)),
    },
    [11] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
    },
    [12] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(110)),
    },
    [13] = {
        [sym_type_specifier] = ACTIONS(SHIFT(14)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_struct_declaration] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(18)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(20)),
    },
    [14] = {
        [sym_declarator] = ACTIONS(SHIFT(32)),
        [sym_direct_declarator] = ACTIONS(SHIFT(33)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(36)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(37)),
    },
    [15] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_star] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1)),
    },
    [16] = {
        [sym_type_specifier] = ACTIONS(SHIFT(14)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_struct_declaration] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(31)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 1)),
    },
    [17] = {
        [sym_identifier] = ACTIONS(SHIFT(30)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(29)),
    },
    [19] = {
        [sym_identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(22)),
    },
    [20] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_star] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
    },
    [21] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(26)),
    },
    [22] = {
        [sym_type_specifier] = ACTIONS(SHIFT(14)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_struct_declaration] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(23)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(24)),
    },
    [23] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(25)),
    },
    [24] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_star] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
    },
    [25] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_star] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
    },
    [26] = {
        [sym_type_specifier] = ACTIONS(SHIFT(14)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_struct_declaration] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(27)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(25)),
    },
    [27] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(28)),
    },
    [28] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_star] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
    },
    [29] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_star] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
    },
    [30] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_star] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 2)),
    },
    [31] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 2)),
    },
    [32] = {
        [sym_type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
    },
    [33] = {
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(102)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(103)),
    },
    [34] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(109)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
    },
    [35] = {
        [sym_type_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
    },
    [36] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(101)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(37)),
    },
    [37] = {
        [sym_declarator] = ACTIONS(SHIFT(38)),
        [sym_direct_declarator] = ACTIONS(SHIFT(39)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(42)),
    },
    [38] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(100)),
    },
    [39] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(46)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(47)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [40] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
    },
    [41] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(45)),
        [sym_identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(42)),
    },
    [42] = {
        [sym_declarator] = ACTIONS(SHIFT(43)),
        [sym_direct_declarator] = ACTIONS(SHIFT(39)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(42)),
    },
    [43] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(44)),
    },
    [44] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
    },
    [45] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(46)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(47)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [46] = {
        [sym_expression] = ACTIONS(SHIFT(99)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_call_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(44)),
    },
    [47] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(48)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(49)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(50)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(44)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [48] = {
        [sym_type_specifier] = ACTIONS(SHIFT(97)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
    },
    [49] = {
        [sym_declarator] = ACTIONS(SHIFT(57)),
        [sym_direct_declarator] = ACTIONS(SHIFT(58)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(59)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(60)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(61)),
    },
    [50] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(53)),
    },
    [51] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(56)),
    },
    [52] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(48)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(49)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(54)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [53] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
    },
    [54] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(55)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_direct_declarator_repeat1, 2)),
    },
    [55] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_direct_declarator_repeat1, 3)),
    },
    [56] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
    },
    [57] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
    },
    [58] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(65)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(66)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [59] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
    },
    [60] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(64)),
        [sym_identifier] = ACTIONS(SHIFT(59)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(61)),
    },
    [61] = {
        [sym_declarator] = ACTIONS(SHIFT(62)),
        [sym_direct_declarator] = ACTIONS(SHIFT(39)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(42)),
    },
    [62] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(63)),
    },
    [63] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
    },
    [64] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(65)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(66)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [65] = {
        [sym_expression] = ACTIONS(SHIFT(71)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_call_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(63)),
    },
    [66] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(48)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(49)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(67)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(63)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [67] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(68)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(69)),
    },
    [68] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(70)),
    },
    [69] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
    },
    [70] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
    },
    [71] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(69)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(75)),
    },
    [72] = {
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [73] = {
        [sym_expression] = ACTIONS(SHIFT(96)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_call_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [sym_expression] = ACTIONS(SHIFT(77)),
        [sym_math_expression] = ACTIONS(SHIFT(78)),
        [sym_call_expression] = ACTIONS(SHIFT(78)),
        [sym_string] = ACTIONS(SHIFT(78)),
        [sym_identifier] = ACTIONS(SHIFT(78)),
        [sym_number] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(79)),
    },
    [75] = {
        [sym_expression] = ACTIONS(SHIFT(76)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_call_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [77] = {
        [sym_star] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(81)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(82)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(85)),
    },
    [78] = {
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [79] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [80] = {
        [sym_expression] = ACTIONS(SHIFT(95)),
        [sym_math_expression] = ACTIONS(SHIFT(78)),
        [sym_call_expression] = ACTIONS(SHIFT(78)),
        [sym_string] = ACTIONS(SHIFT(78)),
        [sym_identifier] = ACTIONS(SHIFT(78)),
        [sym_number] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(94)),
    },
    [82] = {
        [sym_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(78)),
        [sym_call_expression] = ACTIONS(SHIFT(78)),
        [sym_string] = ACTIONS(SHIFT(78)),
        [sym_identifier] = ACTIONS(SHIFT(78)),
        [sym_number] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [sym_expression] = ACTIONS(SHIFT(87)),
        [sym_math_expression] = ACTIONS(SHIFT(78)),
        [sym_call_expression] = ACTIONS(SHIFT(78)),
        [sym_string] = ACTIONS(SHIFT(78)),
        [sym_identifier] = ACTIONS(SHIFT(78)),
        [sym_number] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(88)),
    },
    [84] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [85] = {
        [sym_expression] = ACTIONS(SHIFT(86)),
        [sym_math_expression] = ACTIONS(SHIFT(78)),
        [sym_call_expression] = ACTIONS(SHIFT(78)),
        [sym_string] = ACTIONS(SHIFT(78)),
        [sym_identifier] = ACTIONS(SHIFT(78)),
        [sym_number] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [sym_star] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [87] = {
        [sym_star] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(89)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(82)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(90)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(85)),
    },
    [88] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [89] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(91)),
    },
    [90] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [91] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [92] = {
        [sym_star] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(93)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(82)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(85)),
    },
    [93] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
    },
    [94] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [95] = {
        [sym_star] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [96] = {
        [sym_star] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [97] = {
        [sym_declarator] = ACTIONS(SHIFT(98)),
        [sym_direct_declarator] = ACTIONS(SHIFT(58)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(59)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(60)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(61)),
    },
    [98] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
    },
    [99] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(53)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(75)),
    },
    [100] = {
        [sym_type_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
    },
    [101] = {
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(102)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(103)),
    },
    [102] = {
        [sym_expression] = ACTIONS(SHIFT(108)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_call_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(100)),
    },
    [103] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(48)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(49)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(104)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(100)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [104] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(105)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(106)),
    },
    [105] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(107)),
    },
    [106] = {
        [sym_type_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
    },
    [107] = {
        [sym_type_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
    },
    [108] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(106)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(75)),
    },
    [109] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
    },
    [110] = {
        [sym_type_specifier] = ACTIONS(SHIFT(14)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_struct_declaration] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(111)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(29)),
    },
    [111] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(112)),
    },
    [112] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_star] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
    },
    [113] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_star] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 2)),
    },
    [115] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(254)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(235)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(255)),
    },
    [116] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(131)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(132)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(133)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(134)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(135)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(136)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(137)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [117] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(124)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(125)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [118] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
    },
    [119] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(123)),
        [sym_identifier] = ACTIONS(SHIFT(118)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(120)),
    },
    [120] = {
        [sym_declarator] = ACTIONS(SHIFT(121)),
        [sym_direct_declarator] = ACTIONS(SHIFT(39)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(42)),
    },
    [121] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(122)),
    },
    [122] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
    },
    [123] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(124)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(125)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [124] = {
        [sym_expression] = ACTIONS(SHIFT(130)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_call_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(122)),
    },
    [125] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(48)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(49)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(126)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(122)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [126] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(127)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(128)),
    },
    [127] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(129)),
    },
    [128] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
    },
    [129] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
    },
    [130] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(128)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(75)),
    },
    [131] = {
        [sym_type_specifier] = ACTIONS(SHIFT(250)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(10)),
    },
    [132] = {
        [sym_init_declarator] = ACTIONS(SHIFT(246)),
        [sym_declarator] = ACTIONS(SHIFT(219)),
        [sym_direct_declarator] = ACTIONS(SHIFT(220)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(223)),
    },
    [133] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(131)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(132)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(133)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(245)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [134] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [sym_compound_statement] = ACTIONS(SHIFT(244)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(136)),
    },
    [136] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(196)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(197)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(198)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(199)),
        [sym_math_expression] = ACTIONS(SHIFT(200)),
        [sym_call_expression] = ACTIONS(SHIFT(200)),
        [sym_statement] = ACTIONS(SHIFT(198)),
        [sym_expression_statement] = ACTIONS(SHIFT(201)),
        [sym_string] = ACTIONS(SHIFT(200)),
        [sym_identifier] = ACTIONS(SHIFT(202)),
        [sym_number] = ACTIONS(SHIFT(200)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(203)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(204)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [137] = {
        [sym_initializer] = ACTIONS(SHIFT(138)),
        [sym_expression] = ACTIONS(SHIFT(139)),
        [sym_math_expression] = ACTIONS(SHIFT(140)),
        [sym_call_expression] = ACTIONS(SHIFT(140)),
        [sym_string] = ACTIONS(SHIFT(140)),
        [sym_identifier] = ACTIONS(SHIFT(140)),
        [sym_number] = ACTIONS(SHIFT(140)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(141)),
    },
    [138] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 3)),
    },
    [139] = {
        [sym_star] = ACTIONS(SHIFT(186)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(187)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(188)),
    },
    [140] = {
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [141] = {
        [sym_initializer] = ACTIONS(SHIFT(142)),
        [sym_initializer_list] = ACTIONS(SHIFT(143)),
        [sym_designation] = ACTIONS(SHIFT(144)),
        [sym_expression] = ACTIONS(SHIFT(145)),
        [sym_math_expression] = ACTIONS(SHIFT(146)),
        [sym_call_expression] = ACTIONS(SHIFT(146)),
        [sym_string] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(146)),
        [sym_number] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(147)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(148)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(149)),
    },
    [142] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
    },
    [143] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(183)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(184)),
    },
    [144] = {
        [sym_initializer] = ACTIONS(SHIFT(182)),
        [sym_expression] = ACTIONS(SHIFT(145)),
        [sym_math_expression] = ACTIONS(SHIFT(146)),
        [sym_call_expression] = ACTIONS(SHIFT(146)),
        [sym_string] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(146)),
        [sym_number] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(147)),
    },
    [145] = {
        [sym_star] = ACTIONS(SHIFT(172)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(173)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(174)),
    },
    [146] = {
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [147] = {
        [sym_initializer] = ACTIONS(SHIFT(142)),
        [sym_initializer_list] = ACTIONS(SHIFT(165)),
        [sym_designation] = ACTIONS(SHIFT(144)),
        [sym_expression] = ACTIONS(SHIFT(145)),
        [sym_math_expression] = ACTIONS(SHIFT(146)),
        [sym_call_expression] = ACTIONS(SHIFT(146)),
        [sym_string] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(146)),
        [sym_number] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(147)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(148)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(149)),
    },
    [148] = {
        [sym_expression] = ACTIONS(SHIFT(161)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_call_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(151)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(152)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(153)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(154)),
    },
    [151] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(160)),
    },
    [152] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_designation, 3)),
    },
    [153] = {
        [sym_expression] = ACTIONS(SHIFT(157)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_call_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym_identifier] = ACTIONS(SHIFT(155)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(156)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(153)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(154)),
    },
    [156] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
    },
    [157] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(158)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(75)),
    },
    [158] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(159)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(153)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(154)),
    },
    [159] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
    },
    [160] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_designation, 4)),
    },
    [161] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(162)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(75)),
    },
    [162] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(163)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(160)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(153)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(154)),
    },
    [163] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(164)),
    },
    [164] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_designation, 5)),
    },
    [165] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(166)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(167)),
    },
    [166] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
    },
    [167] = {
        [sym_initializer] = ACTIONS(SHIFT(168)),
        [sym_designation] = ACTIONS(SHIFT(169)),
        [sym_expression] = ACTIONS(SHIFT(145)),
        [sym_math_expression] = ACTIONS(SHIFT(146)),
        [sym_call_expression] = ACTIONS(SHIFT(146)),
        [sym_string] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(146)),
        [sym_number] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(147)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(170)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(148)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(149)),
    },
    [168] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
    },
    [169] = {
        [sym_initializer] = ACTIONS(SHIFT(171)),
        [sym_expression] = ACTIONS(SHIFT(145)),
        [sym_math_expression] = ACTIONS(SHIFT(146)),
        [sym_call_expression] = ACTIONS(SHIFT(146)),
        [sym_string] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(146)),
        [sym_number] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(147)),
    },
    [170] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
    },
    [171] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
    },
    [172] = {
        [sym_expression] = ACTIONS(SHIFT(181)),
        [sym_math_expression] = ACTIONS(SHIFT(146)),
        [sym_call_expression] = ACTIONS(SHIFT(146)),
        [sym_string] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(146)),
        [sym_number] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [sym_expression] = ACTIONS(SHIFT(176)),
        [sym_math_expression] = ACTIONS(SHIFT(78)),
        [sym_call_expression] = ACTIONS(SHIFT(78)),
        [sym_string] = ACTIONS(SHIFT(78)),
        [sym_identifier] = ACTIONS(SHIFT(78)),
        [sym_number] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(177)),
    },
    [174] = {
        [sym_expression] = ACTIONS(SHIFT(175)),
        [sym_math_expression] = ACTIONS(SHIFT(146)),
        [sym_call_expression] = ACTIONS(SHIFT(146)),
        [sym_string] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(146)),
        [sym_number] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [sym_star] = ACTIONS(SHIFT(172)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(173)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [176] = {
        [sym_star] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(178)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(82)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(179)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(85)),
    },
    [177] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [178] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(180)),
    },
    [179] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [180] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [181] = {
        [sym_star] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(173)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [182] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
    },
    [183] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
    },
    [184] = {
        [sym_initializer] = ACTIONS(SHIFT(168)),
        [sym_designation] = ACTIONS(SHIFT(169)),
        [sym_expression] = ACTIONS(SHIFT(145)),
        [sym_math_expression] = ACTIONS(SHIFT(146)),
        [sym_call_expression] = ACTIONS(SHIFT(146)),
        [sym_string] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(146)),
        [sym_number] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(147)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(185)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(148)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(149)),
    },
    [185] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
    },
    [186] = {
        [sym_expression] = ACTIONS(SHIFT(195)),
        [sym_math_expression] = ACTIONS(SHIFT(140)),
        [sym_call_expression] = ACTIONS(SHIFT(140)),
        [sym_string] = ACTIONS(SHIFT(140)),
        [sym_identifier] = ACTIONS(SHIFT(140)),
        [sym_number] = ACTIONS(SHIFT(140)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [sym_expression] = ACTIONS(SHIFT(190)),
        [sym_math_expression] = ACTIONS(SHIFT(78)),
        [sym_call_expression] = ACTIONS(SHIFT(78)),
        [sym_string] = ACTIONS(SHIFT(78)),
        [sym_identifier] = ACTIONS(SHIFT(78)),
        [sym_number] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(191)),
    },
    [188] = {
        [sym_expression] = ACTIONS(SHIFT(189)),
        [sym_math_expression] = ACTIONS(SHIFT(140)),
        [sym_call_expression] = ACTIONS(SHIFT(140)),
        [sym_string] = ACTIONS(SHIFT(140)),
        [sym_identifier] = ACTIONS(SHIFT(140)),
        [sym_number] = ACTIONS(SHIFT(140)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [sym_star] = ACTIONS(SHIFT(186)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(187)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [190] = {
        [sym_star] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(192)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(82)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(193)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(85)),
    },
    [191] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [192] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(194)),
    },
    [193] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [194] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [195] = {
        [sym_star] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(187)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [196] = {
        [sym_type_specifier] = ACTIONS(SHIFT(240)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(10)),
    },
    [197] = {
        [sym_init_declarator] = ACTIONS(SHIFT(218)),
        [sym_declarator] = ACTIONS(SHIFT(219)),
        [sym_direct_declarator] = ACTIONS(SHIFT(220)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(223)),
    },
    [198] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(196)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(197)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(198)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(199)),
        [sym_math_expression] = ACTIONS(SHIFT(200)),
        [sym_call_expression] = ACTIONS(SHIFT(200)),
        [sym_statement] = ACTIONS(SHIFT(198)),
        [sym_expression_statement] = ACTIONS(SHIFT(201)),
        [sym_string] = ACTIONS(SHIFT(200)),
        [sym_identifier] = ACTIONS(SHIFT(202)),
        [sym_number] = ACTIONS(SHIFT(200)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(217)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [199] = {
        [sym_star] = ACTIONS(SHIFT(206)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(207)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(209)),
    },
    [200] = {
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [201] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_expression] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_statement] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_string] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_statement, 1)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_statement, 1)),
    },
    [202] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_star] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym_expression, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [203] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(205)),
    },
    [204] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [sym_expression] = ACTIONS(SHIFT(216)),
        [sym_math_expression] = ACTIONS(SHIFT(200)),
        [sym_call_expression] = ACTIONS(SHIFT(200)),
        [sym_string] = ACTIONS(SHIFT(200)),
        [sym_identifier] = ACTIONS(SHIFT(200)),
        [sym_number] = ACTIONS(SHIFT(200)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_expression_statement, 2)),
    },
    [208] = {
        [sym_expression] = ACTIONS(SHIFT(211)),
        [sym_math_expression] = ACTIONS(SHIFT(78)),
        [sym_call_expression] = ACTIONS(SHIFT(78)),
        [sym_string] = ACTIONS(SHIFT(78)),
        [sym_identifier] = ACTIONS(SHIFT(78)),
        [sym_number] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(212)),
    },
    [209] = {
        [sym_expression] = ACTIONS(SHIFT(210)),
        [sym_math_expression] = ACTIONS(SHIFT(200)),
        [sym_call_expression] = ACTIONS(SHIFT(200)),
        [sym_string] = ACTIONS(SHIFT(200)),
        [sym_identifier] = ACTIONS(SHIFT(200)),
        [sym_number] = ACTIONS(SHIFT(200)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [sym_star] = ACTIONS(SHIFT(206)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [211] = {
        [sym_star] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(213)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(82)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(214)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(85)),
    },
    [212] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [213] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(215)),
    },
    [214] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [215] = {
        [sym_star] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [216] = {
        [sym_star] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [217] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
    },
    [218] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(234)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(235)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(236)),
    },
    [219] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(137)),
    },
    [220] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(228)),
    },
    [221] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
    },
    [222] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(226)),
        [sym_identifier] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(223)),
    },
    [223] = {
        [sym_declarator] = ACTIONS(SHIFT(224)),
        [sym_direct_declarator] = ACTIONS(SHIFT(39)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(42)),
    },
    [224] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(225)),
    },
    [225] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
    },
    [226] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(228)),
    },
    [227] = {
        [sym_expression] = ACTIONS(SHIFT(233)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_call_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(225)),
    },
    [228] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(48)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(49)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(229)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(225)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [229] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(230)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(231)),
    },
    [230] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(232)),
    },
    [231] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
    },
    [232] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
    },
    [233] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(231)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(75)),
    },
    [234] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(239)),
    },
    [235] = {
        [sym_init_declarator] = ACTIONS(SHIFT(237)),
        [sym_declarator] = ACTIONS(SHIFT(219)),
        [sym_direct_declarator] = ACTIONS(SHIFT(220)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(223)),
    },
    [236] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declaration, 3)),
    },
    [237] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(238)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(235)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
    },
    [238] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
    },
    [239] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declaration, 4)),
    },
    [240] = {
        [sym_init_declarator] = ACTIONS(SHIFT(241)),
        [sym_declarator] = ACTIONS(SHIFT(219)),
        [sym_direct_declarator] = ACTIONS(SHIFT(220)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(223)),
    },
    [241] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(242)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(235)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(239)),
    },
    [242] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(243)),
    },
    [243] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declaration, 5)),
    },
    [244] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
    },
    [246] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(247)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(235)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(248)),
    },
    [247] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(249)),
    },
    [248] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declaration, 3)),
    },
    [249] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declaration, 4)),
    },
    [250] = {
        [sym_init_declarator] = ACTIONS(SHIFT(251)),
        [sym_declarator] = ACTIONS(SHIFT(219)),
        [sym_direct_declarator] = ACTIONS(SHIFT(220)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(223)),
    },
    [251] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(235)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(249)),
    },
    [252] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(253)),
    },
    [253] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declaration, 5)),
    },
    [254] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(256)),
    },
    [255] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(257)),
        [sym_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(257)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(259)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [258] = {
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
    },
    [259] = {
        [sym_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
    },
    [260] = {
        [sym_init_declarator] = ACTIONS(SHIFT(261)),
        [sym_declarator] = ACTIONS(SHIFT(262)),
        [sym_direct_declarator] = ACTIONS(SHIFT(117)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(118)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(119)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(120)),
    },
    [261] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(265)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(235)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(256)),
    },
    [262] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(131)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(132)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(133)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(244)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(263)),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(136)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(137)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [263] = {
        [sym_compound_statement] = ACTIONS(SHIFT(264)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(136)),
    },
    [264] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [265] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(266)),
    },
    [266] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
