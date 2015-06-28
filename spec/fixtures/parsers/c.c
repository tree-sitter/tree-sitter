#include "tree_sitter/parser.h"

#define STATE_COUNT 229
#define SYMBOL_COUNT 63

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
    [ts_builtin_sym_ambiguity] = "DOCUMENT",
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
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(121);
            LEX_ERROR();
        case 121:
            ACCEPT_TOKEN(aux_sym_STR_SEMI);
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
                ADVANCE(121);
            if (lookahead == '=')
                ADVANCE(123);
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
        case 123:
            ACCEPT_TOKEN(aux_sym_STR_EQ);
        case 124:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(124);
            if (lookahead == '(')
                ADVANCE(86);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(121);
            if (lookahead == '=')
                ADVANCE(123);
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
        case 125:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
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
        case 126:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
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
                ADVANCE(109);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
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
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(118);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(121);
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
            if (lookahead == '.')
                ADVANCE(130);
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
        case 130:
            ACCEPT_TOKEN(aux_sym_STR_DOT);
        case 131:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(131);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 132:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
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
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '.')
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '=')
                ADVANCE(123);
            if (lookahead == '[')
                ADVANCE(98);
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
                ADVANCE(123);
            LEX_ERROR();
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '\"')
                ADVANCE(104);
            if (lookahead == '.')
                ADVANCE(130);
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
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
            if (lookahead == '*')
                ADVANCE(87);
            if (lookahead == '+')
                ADVANCE(118);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(121);
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
                ADVANCE(118);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(4);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(121);
            if (lookahead == '=')
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
            if (lookahead == ',')
                ADVANCE(115);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(121);
            if (lookahead == '=')
                ADVANCE(123);
            if (lookahead == '[')
                ADVANCE(98);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(121);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(81);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
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
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
            if (lookahead == ';')
                ADVANCE(121);
            if (lookahead == '=')
                ADVANCE(123);
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
                ADVANCE(141);
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
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(109);
            if (lookahead == ';')
                ADVANCE(121);
            if (lookahead == '=')
                ADVANCE(123);
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
    [74] = 119,
    [75] = 117,
    [76] = 117,
    [77] = 85,
    [78] = 114,
    [79] = 117,
    [80] = 97,
    [81] = 97,
    [82] = 103,
    [83] = 113,
    [84] = 114,
    [85] = 100,
    [86] = 97,
    [87] = 97,
    [88] = 117,
    [89] = 99,
    [90] = 94,
    [91] = 96,
    [92] = 85,
    [93] = 88,
    [94] = 85,
    [95] = 120,
    [96] = 122,
    [97] = 124,
    [98] = 124,
    [99] = 99,
    [100] = 85,
    [101] = 100,
    [102] = 124,
    [103] = 124,
    [104] = 103,
    [105] = 113,
    [106] = 114,
    [107] = 100,
    [108] = 124,
    [109] = 124,
    [110] = 117,
    [111] = 82,
    [112] = 85,
    [113] = 125,
    [114] = 80,
    [115] = 93,
    [116] = 126,
    [117] = 127,
    [118] = 120,
    [119] = 128,
    [120] = 128,
    [121] = 129,
    [122] = 131,
    [123] = 131,
    [124] = 127,
    [125] = 132,
    [126] = 132,
    [127] = 129,
    [128] = 119,
    [129] = 88,
    [130] = 133,
    [131] = 134,
    [132] = 127,
    [133] = 119,
    [134] = 88,
    [135] = 133,
    [136] = 134,
    [137] = 117,
    [138] = 133,
    [139] = 134,
    [140] = 127,
    [141] = 117,
    [142] = 133,
    [143] = 134,
    [144] = 127,
    [145] = 131,
    [146] = 131,
    [147] = 135,
    [148] = 131,
    [149] = 127,
    [150] = 131,
    [151] = 131,
    [152] = 119,
    [153] = 119,
    [154] = 132,
    [155] = 132,
    [156] = 131,
    [157] = 120,
    [158] = 135,
    [159] = 120,
    [160] = 119,
    [161] = 119,
    [162] = 128,
    [163] = 128,
    [164] = 82,
    [165] = 85,
    [166] = 126,
    [167] = 136,
    [168] = 136,
    [169] = 126,
    [170] = 137,
    [171] = 96,
    [172] = 80,
    [173] = 80,
    [174] = 119,
    [175] = 126,
    [176] = 119,
    [177] = 136,
    [178] = 136,
    [179] = 96,
    [180] = 120,
    [181] = 138,
    [182] = 139,
    [183] = 139,
    [184] = 99,
    [185] = 85,
    [186] = 100,
    [187] = 139,
    [188] = 139,
    [189] = 103,
    [190] = 113,
    [191] = 114,
    [192] = 100,
    [193] = 139,
    [194] = 139,
    [195] = 117,
    [196] = 140,
    [197] = 85,
    [198] = 126,
    [199] = 120,
    [200] = 140,
    [201] = 126,
    [202] = 85,
    [203] = 120,
    [204] = 140,
    [205] = 126,
    [206] = 80,
    [207] = 93,
    [208] = 120,
    [209] = 140,
    [210] = 125,
    [211] = 125,
    [212] = 85,
    [213] = 120,
    [214] = 140,
    [215] = 125,
    [216] = 140,
    [217] = 80,
    [218] = 80,
    [219] = 1,
    [220] = 82,
    [221] = 82,
    [222] = 85,
    [223] = 120,
    [224] = 122,
    [225] = 93,
    [226] = 80,
    [227] = 140,
    [228] = 80,
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
        [sym_type_specifier] = ACTIONS(SHIFT(222)),
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
        [sym_storage_class_specifier] = ACTIONS(SHIFT(219)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(219)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(220)),
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
        [sym_init_declarator] = ACTIONS(SHIFT(95)),
        [sym_declarator] = ACTIONS(SHIFT(96)),
        [sym_direct_declarator] = ACTIONS(SHIFT(97)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(98)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(99)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(100)),
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
        [sym_identifier] = ACTIONS(SHIFT(94)),
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
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(93)),
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
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(90)),
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(82)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
    },
    [34] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(89)),
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
        [sym_direct_declarator] = ACTIONS(SHIFT(81)),
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
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(80)),
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
        [sym_expression] = ACTIONS(SHIFT(79)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
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
        [sym_type_specifier] = ACTIONS(SHIFT(77)),
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
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(74)),
    },
    [72] = {
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [73] = {
        [sym_expression] = ACTIONS(SHIFT(76)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [sym_expression] = ACTIONS(SHIFT(75)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [75] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [76] = {
        [sym_star] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [77] = {
        [sym_declarator] = ACTIONS(SHIFT(78)),
        [sym_direct_declarator] = ACTIONS(SHIFT(58)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(59)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(60)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(61)),
    },
    [78] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
    },
    [79] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(53)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(74)),
    },
    [80] = {
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
    [81] = {
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(82)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(83)),
    },
    [82] = {
        [sym_expression] = ACTIONS(SHIFT(88)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(80)),
    },
    [83] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(48)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(49)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(84)),
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
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(80)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [84] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(85)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(86)),
    },
    [85] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(87)),
    },
    [86] = {
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
    [87] = {
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
    [88] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(74)),
    },
    [89] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
    },
    [90] = {
        [sym_type_specifier] = ACTIONS(SHIFT(14)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_struct_declaration] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(17)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(91)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(29)),
    },
    [91] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(92)),
    },
    [92] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_star] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
    },
    [93] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_star] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 2)),
    },
    [95] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(216)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(197)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(217)),
    },
    [96] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(111)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(112)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(113)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(114)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(115)),
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
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(116)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(117)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [97] = {
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(104)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(105)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [98] = {
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
    [99] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(103)),
        [sym_identifier] = ACTIONS(SHIFT(98)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(100)),
    },
    [100] = {
        [sym_declarator] = ACTIONS(SHIFT(101)),
        [sym_direct_declarator] = ACTIONS(SHIFT(39)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(42)),
    },
    [101] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(102)),
    },
    [102] = {
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
    [103] = {
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(104)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(105)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [104] = {
        [sym_expression] = ACTIONS(SHIFT(110)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(102)),
    },
    [105] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(48)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(49)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(106)),
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
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(102)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [106] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(107)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(108)),
    },
    [107] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(109)),
    },
    [108] = {
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
    [109] = {
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
    [110] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(108)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(74)),
    },
    [111] = {
        [sym_type_specifier] = ACTIONS(SHIFT(212)),
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
    [112] = {
        [sym_init_declarator] = ACTIONS(SHIFT(208)),
        [sym_declarator] = ACTIONS(SHIFT(181)),
        [sym_direct_declarator] = ACTIONS(SHIFT(182)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(183)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(184)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(185)),
    },
    [113] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(111)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(112)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(113)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(207)),
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
    [114] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [sym_compound_statement] = ACTIONS(SHIFT(206)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(116)),
    },
    [116] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(164)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(165)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(166)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(167)),
        [sym_math_expression] = ACTIONS(SHIFT(168)),
        [sym_statement] = ACTIONS(SHIFT(166)),
        [sym_expression_statement] = ACTIONS(SHIFT(169)),
        [sym_string] = ACTIONS(SHIFT(168)),
        [sym_identifier] = ACTIONS(SHIFT(170)),
        [sym_number] = ACTIONS(SHIFT(168)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(171)),
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
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(172)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [117] = {
        [sym_initializer] = ACTIONS(SHIFT(118)),
        [sym_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(120)),
        [sym_identifier] = ACTIONS(SHIFT(120)),
        [sym_number] = ACTIONS(SHIFT(120)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(121)),
    },
    [118] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 3)),
    },
    [119] = {
        [sym_star] = ACTIONS(SHIFT(160)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(161)),
    },
    [120] = {
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [121] = {
        [sym_initializer] = ACTIONS(SHIFT(122)),
        [sym_initializer_list] = ACTIONS(SHIFT(123)),
        [sym_designation] = ACTIONS(SHIFT(124)),
        [sym_expression] = ACTIONS(SHIFT(125)),
        [sym_math_expression] = ACTIONS(SHIFT(126)),
        [sym_string] = ACTIONS(SHIFT(126)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(126)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(127)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(128)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(129)),
    },
    [122] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
    },
    [123] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(157)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(158)),
    },
    [124] = {
        [sym_initializer] = ACTIONS(SHIFT(156)),
        [sym_expression] = ACTIONS(SHIFT(125)),
        [sym_math_expression] = ACTIONS(SHIFT(126)),
        [sym_string] = ACTIONS(SHIFT(126)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(126)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(127)),
    },
    [125] = {
        [sym_star] = ACTIONS(SHIFT(152)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(153)),
    },
    [126] = {
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [127] = {
        [sym_initializer] = ACTIONS(SHIFT(122)),
        [sym_initializer_list] = ACTIONS(SHIFT(145)),
        [sym_designation] = ACTIONS(SHIFT(124)),
        [sym_expression] = ACTIONS(SHIFT(125)),
        [sym_math_expression] = ACTIONS(SHIFT(126)),
        [sym_string] = ACTIONS(SHIFT(126)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(126)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(127)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(128)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(129)),
    },
    [128] = {
        [sym_expression] = ACTIONS(SHIFT(141)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [sym_identifier] = ACTIONS(SHIFT(130)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(131)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(132)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(133)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(134)),
    },
    [131] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(140)),
    },
    [132] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_designation, 3)),
    },
    [133] = {
        [sym_expression] = ACTIONS(SHIFT(137)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [sym_identifier] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(136)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(133)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(134)),
    },
    [136] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
    },
    [137] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(138)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(74)),
    },
    [138] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(133)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(134)),
    },
    [139] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
    },
    [140] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_designation, 4)),
    },
    [141] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(142)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(74)),
    },
    [142] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(143)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(133)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(134)),
    },
    [143] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(144)),
    },
    [144] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_expression] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_designation, 5)),
    },
    [145] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(146)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(147)),
    },
    [146] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
    },
    [147] = {
        [sym_initializer] = ACTIONS(SHIFT(148)),
        [sym_designation] = ACTIONS(SHIFT(149)),
        [sym_expression] = ACTIONS(SHIFT(125)),
        [sym_math_expression] = ACTIONS(SHIFT(126)),
        [sym_string] = ACTIONS(SHIFT(126)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(126)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(127)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(150)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(128)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(129)),
    },
    [148] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
    },
    [149] = {
        [sym_initializer] = ACTIONS(SHIFT(151)),
        [sym_expression] = ACTIONS(SHIFT(125)),
        [sym_math_expression] = ACTIONS(SHIFT(126)),
        [sym_string] = ACTIONS(SHIFT(126)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(126)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(127)),
    },
    [150] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
    },
    [151] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
    },
    [152] = {
        [sym_expression] = ACTIONS(SHIFT(155)),
        [sym_math_expression] = ACTIONS(SHIFT(126)),
        [sym_string] = ACTIONS(SHIFT(126)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(126)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [sym_expression] = ACTIONS(SHIFT(154)),
        [sym_math_expression] = ACTIONS(SHIFT(126)),
        [sym_string] = ACTIONS(SHIFT(126)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(126)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym_star] = ACTIONS(SHIFT(152)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [155] = {
        [sym_star] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [156] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
    },
    [157] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
    },
    [158] = {
        [sym_initializer] = ACTIONS(SHIFT(148)),
        [sym_designation] = ACTIONS(SHIFT(149)),
        [sym_expression] = ACTIONS(SHIFT(125)),
        [sym_math_expression] = ACTIONS(SHIFT(126)),
        [sym_string] = ACTIONS(SHIFT(126)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(126)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(127)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(159)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(128)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(129)),
    },
    [159] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
    },
    [160] = {
        [sym_expression] = ACTIONS(SHIFT(163)),
        [sym_math_expression] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(120)),
        [sym_identifier] = ACTIONS(SHIFT(120)),
        [sym_number] = ACTIONS(SHIFT(120)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [sym_expression] = ACTIONS(SHIFT(162)),
        [sym_math_expression] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(120)),
        [sym_identifier] = ACTIONS(SHIFT(120)),
        [sym_number] = ACTIONS(SHIFT(120)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [sym_star] = ACTIONS(SHIFT(160)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [163] = {
        [sym_star] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [164] = {
        [sym_type_specifier] = ACTIONS(SHIFT(202)),
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
    [165] = {
        [sym_init_declarator] = ACTIONS(SHIFT(180)),
        [sym_declarator] = ACTIONS(SHIFT(181)),
        [sym_direct_declarator] = ACTIONS(SHIFT(182)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(183)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(184)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(185)),
    },
    [166] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(164)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(165)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(166)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(167)),
        [sym_math_expression] = ACTIONS(SHIFT(168)),
        [sym_statement] = ACTIONS(SHIFT(166)),
        [sym_expression_statement] = ACTIONS(SHIFT(169)),
        [sym_string] = ACTIONS(SHIFT(168)),
        [sym_identifier] = ACTIONS(SHIFT(170)),
        [sym_number] = ACTIONS(SHIFT(168)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_specifier_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(179)),
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
    [167] = {
        [sym_star] = ACTIONS(SHIFT(174)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(175)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(176)),
    },
    [168] = {
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [169] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_expression] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_statement, 1)),
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
    [170] = {
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_star] = ACTIONS(REDUCE(sym_expression, 1), REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [171] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(173)),
    },
    [172] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [sym_expression] = ACTIONS(SHIFT(178)),
        [sym_math_expression] = ACTIONS(SHIFT(168)),
        [sym_string] = ACTIONS(SHIFT(168)),
        [sym_identifier] = ACTIONS(SHIFT(168)),
        [sym_number] = ACTIONS(SHIFT(168)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
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
    [176] = {
        [sym_expression] = ACTIONS(SHIFT(177)),
        [sym_math_expression] = ACTIONS(SHIFT(168)),
        [sym_string] = ACTIONS(SHIFT(168)),
        [sym_identifier] = ACTIONS(SHIFT(168)),
        [sym_number] = ACTIONS(SHIFT(168)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [sym_star] = ACTIONS(SHIFT(174)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [178] = {
        [sym_star] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [179] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
    },
    [180] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(196)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(197)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(198)),
    },
    [181] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(117)),
    },
    [182] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(189)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(190)),
    },
    [183] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
    },
    [184] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(188)),
        [sym_identifier] = ACTIONS(SHIFT(183)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(185)),
    },
    [185] = {
        [sym_declarator] = ACTIONS(SHIFT(186)),
        [sym_direct_declarator] = ACTIONS(SHIFT(39)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(42)),
    },
    [186] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(187)),
    },
    [187] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
    },
    [188] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(189)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(190)),
    },
    [189] = {
        [sym_expression] = ACTIONS(SHIFT(195)),
        [sym_math_expression] = ACTIONS(SHIFT(72)),
        [sym_string] = ACTIONS(SHIFT(72)),
        [sym_identifier] = ACTIONS(SHIFT(72)),
        [sym_number] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(187)),
    },
    [190] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(48)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(49)),
        [sym_struct_specifier] = ACTIONS(SHIFT(15)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(191)),
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
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(187)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [191] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(192)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(193)),
    },
    [192] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(194)),
    },
    [193] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
    },
    [194] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
    },
    [195] = {
        [sym_star] = ACTIONS(SHIFT(73)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(193)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(74)),
    },
    [196] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(201)),
    },
    [197] = {
        [sym_init_declarator] = ACTIONS(SHIFT(199)),
        [sym_declarator] = ACTIONS(SHIFT(181)),
        [sym_direct_declarator] = ACTIONS(SHIFT(182)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(183)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(184)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(185)),
    },
    [198] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
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
    [199] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(200)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(197)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
    },
    [200] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
    },
    [201] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
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
    [202] = {
        [sym_init_declarator] = ACTIONS(SHIFT(203)),
        [sym_declarator] = ACTIONS(SHIFT(181)),
        [sym_direct_declarator] = ACTIONS(SHIFT(182)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(183)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(184)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(185)),
    },
    [203] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(204)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(197)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(201)),
    },
    [204] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(205)),
    },
    [205] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
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
    [206] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
    },
    [208] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(209)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(197)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(210)),
    },
    [209] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(211)),
    },
    [210] = {
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
    [211] = {
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
    [212] = {
        [sym_init_declarator] = ACTIONS(SHIFT(213)),
        [sym_declarator] = ACTIONS(SHIFT(181)),
        [sym_direct_declarator] = ACTIONS(SHIFT(182)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(183)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(184)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(185)),
    },
    [213] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(214)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(197)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(211)),
    },
    [214] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(215)),
    },
    [215] = {
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
    [216] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(218)),
    },
    [217] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [219] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(219)),
        [sym_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(219)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(221)),
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
    [220] = {
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
    [221] = {
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
    [222] = {
        [sym_init_declarator] = ACTIONS(SHIFT(223)),
        [sym_declarator] = ACTIONS(SHIFT(224)),
        [sym_direct_declarator] = ACTIONS(SHIFT(97)),
        [sym_star] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(98)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(99)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(100)),
    },
    [223] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(197)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(218)),
    },
    [224] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(111)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym_type_specifier] = ACTIONS(SHIFT(112)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(113)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(206)),
        [sym_identifier] = ACTIONS(SHIFT(6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(225)),
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
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(116)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(117)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(11)),
    },
    [225] = {
        [sym_compound_statement] = ACTIONS(SHIFT(226)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(116)),
    },
    [226] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(228)),
    },
    [228] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
