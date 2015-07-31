#include "tree_sitter/parser.h"

#define STATE_COUNT 268
#define SYMBOL_COUNT 65

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
    sym_pointer,
    sym_compound_statement,
    sym_expression,
    sym_math_expression,
    sym_call_expression,
    sym_statement,
    sym_expression_statement,
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
    aux_sym_STR_STAR,
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
    [sym_pointer] = "pointer",
    [sym_compound_statement] = "compound_statement",
    [sym_expression] = "expression",
    [sym_math_expression] = "math_expression",
    [sym_call_expression] = "call_expression",
    [sym_statement] = "statement",
    [sym_expression_statement] = "expression_statement",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
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
    [aux_sym_STR_STAR] = "STR_*",
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
    [aux_sym_STR_STAR] = 1,
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
            ACCEPT_TOKEN(aux_sym_STR_STAR);
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
    [38] = 85,
    [39] = 100,
    [40] = 102,
    [41] = 102,
    [42] = 99,
    [43] = 85,
    [44] = 100,
    [45] = 102,
    [46] = 102,
    [47] = 103,
    [48] = 113,
    [49] = 82,
    [50] = 85,
    [51] = 114,
    [52] = 100,
    [53] = 1,
    [54] = 102,
    [55] = 114,
    [56] = 100,
    [57] = 102,
    [58] = 114,
    [59] = 116,
    [60] = 116,
    [61] = 99,
    [62] = 85,
    [63] = 100,
    [64] = 116,
    [65] = 116,
    [66] = 103,
    [67] = 113,
    [68] = 114,
    [69] = 100,
    [70] = 116,
    [71] = 116,
    [72] = 117,
    [73] = 117,
    [74] = 119,
    [75] = 120,
    [76] = 120,
    [77] = 117,
    [78] = 117,
    [79] = 121,
    [80] = 121,
    [81] = 117,
    [82] = 100,
    [83] = 120,
    [84] = 119,
    [85] = 117,
    [86] = 120,
    [87] = 120,
    [88] = 121,
    [89] = 121,
    [90] = 121,
    [91] = 121,
    [92] = 100,
    [93] = 121,
    [94] = 121,
    [95] = 121,
    [96] = 100,
    [97] = 117,
    [98] = 85,
    [99] = 114,
    [100] = 117,
    [101] = 97,
    [102] = 97,
    [103] = 103,
    [104] = 113,
    [105] = 114,
    [106] = 100,
    [107] = 97,
    [108] = 97,
    [109] = 117,
    [110] = 99,
    [111] = 94,
    [112] = 96,
    [113] = 85,
    [114] = 88,
    [115] = 85,
    [116] = 122,
    [117] = 124,
    [118] = 126,
    [119] = 126,
    [120] = 99,
    [121] = 85,
    [122] = 100,
    [123] = 126,
    [124] = 126,
    [125] = 103,
    [126] = 113,
    [127] = 114,
    [128] = 100,
    [129] = 126,
    [130] = 126,
    [131] = 117,
    [132] = 82,
    [133] = 85,
    [134] = 127,
    [135] = 80,
    [136] = 93,
    [137] = 128,
    [138] = 129,
    [139] = 122,
    [140] = 130,
    [141] = 130,
    [142] = 131,
    [143] = 133,
    [144] = 133,
    [145] = 129,
    [146] = 134,
    [147] = 134,
    [148] = 131,
    [149] = 120,
    [150] = 88,
    [151] = 135,
    [152] = 136,
    [153] = 129,
    [154] = 120,
    [155] = 88,
    [156] = 135,
    [157] = 136,
    [158] = 117,
    [159] = 135,
    [160] = 136,
    [161] = 129,
    [162] = 117,
    [163] = 135,
    [164] = 136,
    [165] = 129,
    [166] = 133,
    [167] = 133,
    [168] = 137,
    [169] = 133,
    [170] = 129,
    [171] = 133,
    [172] = 133,
    [173] = 119,
    [174] = 120,
    [175] = 120,
    [176] = 134,
    [177] = 134,
    [178] = 121,
    [179] = 134,
    [180] = 100,
    [181] = 134,
    [182] = 134,
    [183] = 133,
    [184] = 122,
    [185] = 137,
    [186] = 122,
    [187] = 119,
    [188] = 120,
    [189] = 120,
    [190] = 130,
    [191] = 130,
    [192] = 121,
    [193] = 130,
    [194] = 100,
    [195] = 130,
    [196] = 130,
    [197] = 82,
    [198] = 85,
    [199] = 128,
    [200] = 138,
    [201] = 138,
    [202] = 128,
    [203] = 139,
    [204] = 96,
    [205] = 80,
    [206] = 80,
    [207] = 128,
    [208] = 119,
    [209] = 120,
    [210] = 120,
    [211] = 138,
    [212] = 138,
    [213] = 121,
    [214] = 138,
    [215] = 100,
    [216] = 138,
    [217] = 138,
    [218] = 96,
    [219] = 122,
    [220] = 140,
    [221] = 141,
    [222] = 141,
    [223] = 99,
    [224] = 85,
    [225] = 100,
    [226] = 141,
    [227] = 141,
    [228] = 103,
    [229] = 113,
    [230] = 114,
    [231] = 100,
    [232] = 141,
    [233] = 141,
    [234] = 117,
    [235] = 142,
    [236] = 85,
    [237] = 128,
    [238] = 122,
    [239] = 142,
    [240] = 128,
    [241] = 85,
    [242] = 122,
    [243] = 142,
    [244] = 128,
    [245] = 80,
    [246] = 93,
    [247] = 122,
    [248] = 142,
    [249] = 127,
    [250] = 127,
    [251] = 85,
    [252] = 122,
    [253] = 142,
    [254] = 127,
    [255] = 142,
    [256] = 80,
    [257] = 80,
    [258] = 1,
    [259] = 82,
    [260] = 82,
    [261] = 85,
    [262] = 122,
    [263] = 124,
    [264] = 93,
    [265] = 80,
    [266] = 142,
    [267] = 80,
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
        [sym_type_specifier] = ACTIONS(SHIFT(261)),
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
        [sym_storage_class_specifier] = ACTIONS(SHIFT(258)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(258)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(259)),
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
        [sym_init_declarator] = ACTIONS(SHIFT(116)),
        [sym_declarator] = ACTIONS(SHIFT(117)),
        [sym_direct_declarator] = ACTIONS(SHIFT(118)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(120)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(121)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [6] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
    },
    [7] = {
        [sym_identifier] = ACTIONS(SHIFT(115)),
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
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(114)),
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
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(111)),
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
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(36)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(37)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [15] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
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
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
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
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
    },
    [25] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
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
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
    },
    [29] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
    },
    [30] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_specifier, 2)),
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(103)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(104)),
    },
    [34] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(110)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
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
        [sym_direct_declarator] = ACTIONS(SHIFT(102)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(37)),
    },
    [37] = {
        [sym_declarator] = ACTIONS(SHIFT(39)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(42)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(43)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [38] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_pointer, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_pointer, 1)),
    },
    [39] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(101)),
    },
    [40] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(47)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [41] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
    },
    [42] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(46)),
        [sym_identifier] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(43)),
    },
    [43] = {
        [sym_declarator] = ACTIONS(SHIFT(44)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(42)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(43)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [44] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(45)),
    },
    [45] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
    },
    [46] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(47)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [47] = {
        [sym_expression] = ACTIONS(SHIFT(100)),
        [sym_math_expression] = ACTIONS(SHIFT(73)),
        [sym_call_expression] = ACTIONS(SHIFT(73)),
        [sym_string] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(73)),
        [sym_number] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(45)),
    },
    [48] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(49)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(51)),
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
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [49] = {
        [sym_type_specifier] = ACTIONS(SHIFT(98)),
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
    [50] = {
        [sym_declarator] = ACTIONS(SHIFT(58)),
        [sym_direct_declarator] = ACTIONS(SHIFT(59)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(60)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(61)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(62)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [51] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(54)),
    },
    [52] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(57)),
    },
    [53] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(49)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(55)),
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
    [54] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
    },
    [55] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(56)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_direct_declarator_repeat1, 2)),
    },
    [56] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_direct_declarator_repeat1, 3)),
    },
    [57] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
    },
    [58] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
    },
    [59] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(66)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(67)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [60] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
    },
    [61] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(65)),
        [sym_identifier] = ACTIONS(SHIFT(60)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(62)),
    },
    [62] = {
        [sym_declarator] = ACTIONS(SHIFT(63)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(42)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(43)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [63] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(64)),
    },
    [64] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
    },
    [65] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(66)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(67)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [66] = {
        [sym_expression] = ACTIONS(SHIFT(72)),
        [sym_math_expression] = ACTIONS(SHIFT(73)),
        [sym_call_expression] = ACTIONS(SHIFT(73)),
        [sym_string] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(73)),
        [sym_number] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(64)),
    },
    [67] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(49)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(68)),
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
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(64)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [68] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(69)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(70)),
    },
    [69] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(71)),
    },
    [70] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
    },
    [71] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
    },
    [72] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(70)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(75)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(76)),
    },
    [73] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [74] = {
        [sym_expression] = ACTIONS(SHIFT(79)),
        [sym_math_expression] = ACTIONS(SHIFT(80)),
        [sym_call_expression] = ACTIONS(SHIFT(80)),
        [sym_string] = ACTIONS(SHIFT(80)),
        [sym_identifier] = ACTIONS(SHIFT(80)),
        [sym_number] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(81)),
    },
    [75] = {
        [sym_expression] = ACTIONS(SHIFT(78)),
        [sym_math_expression] = ACTIONS(SHIFT(73)),
        [sym_call_expression] = ACTIONS(SHIFT(73)),
        [sym_string] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(73)),
        [sym_number] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [sym_expression] = ACTIONS(SHIFT(77)),
        [sym_math_expression] = ACTIONS(SHIFT(73)),
        [sym_call_expression] = ACTIONS(SHIFT(73)),
        [sym_string] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(73)),
        [sym_number] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(75)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [78] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [79] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(82)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(85)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(87)),
    },
    [80] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [81] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [82] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(97)),
    },
    [83] = {
        [sym_expression] = ACTIONS(SHIFT(95)),
        [sym_math_expression] = ACTIONS(SHIFT(80)),
        [sym_call_expression] = ACTIONS(SHIFT(80)),
        [sym_string] = ACTIONS(SHIFT(80)),
        [sym_identifier] = ACTIONS(SHIFT(80)),
        [sym_number] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [sym_expression] = ACTIONS(SHIFT(90)),
        [sym_math_expression] = ACTIONS(SHIFT(80)),
        [sym_call_expression] = ACTIONS(SHIFT(80)),
        [sym_string] = ACTIONS(SHIFT(80)),
        [sym_identifier] = ACTIONS(SHIFT(80)),
        [sym_number] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(91)),
    },
    [85] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [86] = {
        [sym_expression] = ACTIONS(SHIFT(89)),
        [sym_math_expression] = ACTIONS(SHIFT(80)),
        [sym_call_expression] = ACTIONS(SHIFT(80)),
        [sym_string] = ACTIONS(SHIFT(80)),
        [sym_identifier] = ACTIONS(SHIFT(80)),
        [sym_number] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [sym_expression] = ACTIONS(SHIFT(88)),
        [sym_math_expression] = ACTIONS(SHIFT(80)),
        [sym_call_expression] = ACTIONS(SHIFT(80)),
        [sym_string] = ACTIONS(SHIFT(80)),
        [sym_identifier] = ACTIONS(SHIFT(80)),
        [sym_number] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [89] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [90] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(92)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(93)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(87)),
    },
    [91] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [92] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(94)),
    },
    [93] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [94] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [95] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(96)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(87)),
    },
    [96] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
    },
    [97] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [98] = {
        [sym_declarator] = ACTIONS(SHIFT(99)),
        [sym_direct_declarator] = ACTIONS(SHIFT(59)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(60)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(61)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(62)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [99] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
    },
    [100] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(54)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(75)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(76)),
    },
    [101] = {
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
    [102] = {
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(103)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(104)),
    },
    [103] = {
        [sym_expression] = ACTIONS(SHIFT(109)),
        [sym_math_expression] = ACTIONS(SHIFT(73)),
        [sym_call_expression] = ACTIONS(SHIFT(73)),
        [sym_string] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(73)),
        [sym_number] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(101)),
    },
    [104] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(49)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(105)),
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
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(101)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [105] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(106)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(107)),
    },
    [106] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(108)),
    },
    [107] = {
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
    [108] = {
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
    [109] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(107)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(75)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(76)),
    },
    [110] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
    },
    [111] = {
        [sym_type_specifier] = ACTIONS(SHIFT(14)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_struct_declaration] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(112)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(29)),
    },
    [112] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(113)),
    },
    [113] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
    },
    [114] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_specifier, 2)),
    },
    [116] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(255)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(236)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(256)),
    },
    [117] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(132)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(133)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(134)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(135)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(136)),
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
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(137)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(138)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [118] = {
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(125)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(126)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [119] = {
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
    [120] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(124)),
        [sym_identifier] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(121)),
    },
    [121] = {
        [sym_declarator] = ACTIONS(SHIFT(122)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(42)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(43)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [122] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(123)),
    },
    [123] = {
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
    [124] = {
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(125)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(126)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [125] = {
        [sym_expression] = ACTIONS(SHIFT(131)),
        [sym_math_expression] = ACTIONS(SHIFT(73)),
        [sym_call_expression] = ACTIONS(SHIFT(73)),
        [sym_string] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(73)),
        [sym_number] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(123)),
    },
    [126] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(49)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(127)),
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
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(123)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [127] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(128)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(129)),
    },
    [128] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(130)),
    },
    [129] = {
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
    [130] = {
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
    [131] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(129)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(75)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(76)),
    },
    [132] = {
        [sym_type_specifier] = ACTIONS(SHIFT(251)),
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
    [133] = {
        [sym_init_declarator] = ACTIONS(SHIFT(247)),
        [sym_declarator] = ACTIONS(SHIFT(220)),
        [sym_direct_declarator] = ACTIONS(SHIFT(221)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(222)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [134] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(132)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(133)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(134)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(246)),
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
    [135] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [sym_compound_statement] = ACTIONS(SHIFT(245)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(137)),
    },
    [137] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(197)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(198)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(199)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(200)),
        [sym_math_expression] = ACTIONS(SHIFT(201)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_statement] = ACTIONS(SHIFT(199)),
        [sym_expression_statement] = ACTIONS(SHIFT(202)),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym_identifier] = ACTIONS(SHIFT(203)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(204)),
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
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(205)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [138] = {
        [sym_initializer] = ACTIONS(SHIFT(139)),
        [sym_expression] = ACTIONS(SHIFT(140)),
        [sym_math_expression] = ACTIONS(SHIFT(141)),
        [sym_call_expression] = ACTIONS(SHIFT(141)),
        [sym_string] = ACTIONS(SHIFT(141)),
        [sym_identifier] = ACTIONS(SHIFT(141)),
        [sym_number] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(142)),
    },
    [139] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 3)),
    },
    [140] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(187)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(188)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(189)),
    },
    [141] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [142] = {
        [sym_initializer] = ACTIONS(SHIFT(143)),
        [sym_initializer_list] = ACTIONS(SHIFT(144)),
        [sym_designation] = ACTIONS(SHIFT(145)),
        [sym_expression] = ACTIONS(SHIFT(146)),
        [sym_math_expression] = ACTIONS(SHIFT(147)),
        [sym_call_expression] = ACTIONS(SHIFT(147)),
        [sym_string] = ACTIONS(SHIFT(147)),
        [sym_identifier] = ACTIONS(SHIFT(147)),
        [sym_number] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(148)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(149)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(150)),
    },
    [143] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
    },
    [144] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(184)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(185)),
    },
    [145] = {
        [sym_initializer] = ACTIONS(SHIFT(183)),
        [sym_expression] = ACTIONS(SHIFT(146)),
        [sym_math_expression] = ACTIONS(SHIFT(147)),
        [sym_call_expression] = ACTIONS(SHIFT(147)),
        [sym_string] = ACTIONS(SHIFT(147)),
        [sym_identifier] = ACTIONS(SHIFT(147)),
        [sym_number] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(148)),
    },
    [146] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(173)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(174)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(175)),
    },
    [147] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [148] = {
        [sym_initializer] = ACTIONS(SHIFT(143)),
        [sym_initializer_list] = ACTIONS(SHIFT(166)),
        [sym_designation] = ACTIONS(SHIFT(145)),
        [sym_expression] = ACTIONS(SHIFT(146)),
        [sym_math_expression] = ACTIONS(SHIFT(147)),
        [sym_call_expression] = ACTIONS(SHIFT(147)),
        [sym_string] = ACTIONS(SHIFT(147)),
        [sym_identifier] = ACTIONS(SHIFT(147)),
        [sym_number] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(148)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(149)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(150)),
    },
    [149] = {
        [sym_expression] = ACTIONS(SHIFT(162)),
        [sym_math_expression] = ACTIONS(SHIFT(73)),
        [sym_call_expression] = ACTIONS(SHIFT(73)),
        [sym_string] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(73)),
        [sym_number] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [sym_identifier] = ACTIONS(SHIFT(151)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(152)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(153)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(154)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(155)),
    },
    [152] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(161)),
    },
    [153] = {
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
    [154] = {
        [sym_expression] = ACTIONS(SHIFT(158)),
        [sym_math_expression] = ACTIONS(SHIFT(73)),
        [sym_call_expression] = ACTIONS(SHIFT(73)),
        [sym_string] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(73)),
        [sym_number] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [sym_identifier] = ACTIONS(SHIFT(156)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(157)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(154)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(155)),
    },
    [157] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
    },
    [158] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(159)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(75)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(76)),
    },
    [159] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(160)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(154)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(155)),
    },
    [160] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
    },
    [161] = {
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
    [162] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(163)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(75)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(76)),
    },
    [163] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(164)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(161)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(154)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(155)),
    },
    [164] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(165)),
    },
    [165] = {
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
    [166] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(167)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(168)),
    },
    [167] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
    },
    [168] = {
        [sym_initializer] = ACTIONS(SHIFT(169)),
        [sym_designation] = ACTIONS(SHIFT(170)),
        [sym_expression] = ACTIONS(SHIFT(146)),
        [sym_math_expression] = ACTIONS(SHIFT(147)),
        [sym_call_expression] = ACTIONS(SHIFT(147)),
        [sym_string] = ACTIONS(SHIFT(147)),
        [sym_identifier] = ACTIONS(SHIFT(147)),
        [sym_number] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(148)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(171)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(149)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(150)),
    },
    [169] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
    },
    [170] = {
        [sym_initializer] = ACTIONS(SHIFT(172)),
        [sym_expression] = ACTIONS(SHIFT(146)),
        [sym_math_expression] = ACTIONS(SHIFT(147)),
        [sym_call_expression] = ACTIONS(SHIFT(147)),
        [sym_string] = ACTIONS(SHIFT(147)),
        [sym_identifier] = ACTIONS(SHIFT(147)),
        [sym_number] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(148)),
    },
    [171] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
    },
    [172] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
    },
    [173] = {
        [sym_expression] = ACTIONS(SHIFT(178)),
        [sym_math_expression] = ACTIONS(SHIFT(80)),
        [sym_call_expression] = ACTIONS(SHIFT(80)),
        [sym_string] = ACTIONS(SHIFT(80)),
        [sym_identifier] = ACTIONS(SHIFT(80)),
        [sym_number] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(179)),
    },
    [174] = {
        [sym_expression] = ACTIONS(SHIFT(177)),
        [sym_math_expression] = ACTIONS(SHIFT(147)),
        [sym_call_expression] = ACTIONS(SHIFT(147)),
        [sym_string] = ACTIONS(SHIFT(147)),
        [sym_identifier] = ACTIONS(SHIFT(147)),
        [sym_number] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [sym_expression] = ACTIONS(SHIFT(176)),
        [sym_math_expression] = ACTIONS(SHIFT(147)),
        [sym_call_expression] = ACTIONS(SHIFT(147)),
        [sym_string] = ACTIONS(SHIFT(147)),
        [sym_identifier] = ACTIONS(SHIFT(147)),
        [sym_number] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(173)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(174)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [177] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(173)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [178] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(180)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(181)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(87)),
    },
    [179] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [180] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(182)),
    },
    [181] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [182] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [183] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
    },
    [184] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
    },
    [185] = {
        [sym_initializer] = ACTIONS(SHIFT(169)),
        [sym_designation] = ACTIONS(SHIFT(170)),
        [sym_expression] = ACTIONS(SHIFT(146)),
        [sym_math_expression] = ACTIONS(SHIFT(147)),
        [sym_call_expression] = ACTIONS(SHIFT(147)),
        [sym_string] = ACTIONS(SHIFT(147)),
        [sym_identifier] = ACTIONS(SHIFT(147)),
        [sym_number] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(148)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(186)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(149)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(150)),
    },
    [186] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
    },
    [187] = {
        [sym_expression] = ACTIONS(SHIFT(192)),
        [sym_math_expression] = ACTIONS(SHIFT(80)),
        [sym_call_expression] = ACTIONS(SHIFT(80)),
        [sym_string] = ACTIONS(SHIFT(80)),
        [sym_identifier] = ACTIONS(SHIFT(80)),
        [sym_number] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(193)),
    },
    [188] = {
        [sym_expression] = ACTIONS(SHIFT(191)),
        [sym_math_expression] = ACTIONS(SHIFT(141)),
        [sym_call_expression] = ACTIONS(SHIFT(141)),
        [sym_string] = ACTIONS(SHIFT(141)),
        [sym_identifier] = ACTIONS(SHIFT(141)),
        [sym_number] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [sym_expression] = ACTIONS(SHIFT(190)),
        [sym_math_expression] = ACTIONS(SHIFT(141)),
        [sym_call_expression] = ACTIONS(SHIFT(141)),
        [sym_string] = ACTIONS(SHIFT(141)),
        [sym_identifier] = ACTIONS(SHIFT(141)),
        [sym_number] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(187)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(188)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [191] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(187)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [192] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(194)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(195)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(87)),
    },
    [193] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [194] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(196)),
    },
    [195] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [196] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [197] = {
        [sym_type_specifier] = ACTIONS(SHIFT(241)),
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
    [198] = {
        [sym_init_declarator] = ACTIONS(SHIFT(219)),
        [sym_declarator] = ACTIONS(SHIFT(220)),
        [sym_direct_declarator] = ACTIONS(SHIFT(221)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(222)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [199] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(197)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(198)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(199)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(200)),
        [sym_math_expression] = ACTIONS(SHIFT(201)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_statement] = ACTIONS(SHIFT(199)),
        [sym_expression_statement] = ACTIONS(SHIFT(202)),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym_identifier] = ACTIONS(SHIFT(203)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(218)),
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
    [200] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(207)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(209)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(210)),
    },
    [201] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [202] = {
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
    [203] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [204] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(206)),
    },
    [205] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 3)),
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
        [sym_expression] = ACTIONS(SHIFT(213)),
        [sym_math_expression] = ACTIONS(SHIFT(80)),
        [sym_call_expression] = ACTIONS(SHIFT(80)),
        [sym_string] = ACTIONS(SHIFT(80)),
        [sym_identifier] = ACTIONS(SHIFT(80)),
        [sym_number] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(214)),
    },
    [209] = {
        [sym_expression] = ACTIONS(SHIFT(212)),
        [sym_math_expression] = ACTIONS(SHIFT(201)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym_identifier] = ACTIONS(SHIFT(201)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [sym_expression] = ACTIONS(SHIFT(211)),
        [sym_math_expression] = ACTIONS(SHIFT(201)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym_identifier] = ACTIONS(SHIFT(201)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(209)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [212] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [213] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(215)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(216)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(87)),
    },
    [214] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [215] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(217)),
    },
    [216] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [217] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [218] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
    },
    [219] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(235)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(236)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(237)),
    },
    [220] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(138)),
    },
    [221] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(228)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(229)),
    },
    [222] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
    },
    [223] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(227)),
        [sym_identifier] = ACTIONS(SHIFT(222)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(224)),
    },
    [224] = {
        [sym_declarator] = ACTIONS(SHIFT(225)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(42)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(43)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [225] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(226)),
    },
    [226] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
    },
    [227] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(228)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(229)),
    },
    [228] = {
        [sym_expression] = ACTIONS(SHIFT(234)),
        [sym_math_expression] = ACTIONS(SHIFT(73)),
        [sym_call_expression] = ACTIONS(SHIFT(73)),
        [sym_string] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(73)),
        [sym_number] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(226)),
    },
    [229] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(49)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(230)),
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
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [230] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(231)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(232)),
    },
    [231] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(233)),
    },
    [232] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
    },
    [233] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
    },
    [234] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(232)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(75)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(76)),
    },
    [235] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(240)),
    },
    [236] = {
        [sym_init_declarator] = ACTIONS(SHIFT(238)),
        [sym_declarator] = ACTIONS(SHIFT(220)),
        [sym_direct_declarator] = ACTIONS(SHIFT(221)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(222)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [237] = {
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
    [238] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(239)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(236)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
    },
    [239] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
    },
    [240] = {
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
    [241] = {
        [sym_init_declarator] = ACTIONS(SHIFT(242)),
        [sym_declarator] = ACTIONS(SHIFT(220)),
        [sym_direct_declarator] = ACTIONS(SHIFT(221)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(222)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [242] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(243)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(236)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(240)),
    },
    [243] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(244)),
    },
    [244] = {
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
    [245] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [246] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
    },
    [247] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(248)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(236)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(249)),
    },
    [248] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(250)),
    },
    [249] = {
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
    [250] = {
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
    [251] = {
        [sym_init_declarator] = ACTIONS(SHIFT(252)),
        [sym_declarator] = ACTIONS(SHIFT(220)),
        [sym_direct_declarator] = ACTIONS(SHIFT(221)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(222)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [252] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(253)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(236)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(250)),
    },
    [253] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(254)),
    },
    [254] = {
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
    [255] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(257)),
    },
    [256] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(258)),
        [sym_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(258)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(260)),
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
    [259] = {
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
    [260] = {
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
    [261] = {
        [sym_init_declarator] = ACTIONS(SHIFT(262)),
        [sym_declarator] = ACTIONS(SHIFT(263)),
        [sym_direct_declarator] = ACTIONS(SHIFT(118)),
        [sym_pointer] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(120)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(121)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(38)),
    },
    [262] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(266)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(236)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(257)),
    },
    [263] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(132)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(133)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(134)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(245)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(264)),
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
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(137)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(138)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [264] = {
        [sym_compound_statement] = ACTIONS(SHIFT(265)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(137)),
    },
    [265] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(267)),
    },
    [267] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
