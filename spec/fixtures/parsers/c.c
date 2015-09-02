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
    sym_string,
    sym_identifier,
    sym_number,
    sym_comment,
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
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
    [sym_string] = "string",
    [sym_identifier] = "identifier",
    [sym_number] = "number",
    [sym_comment] = "comment",
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
    [sym__type_specifier] = 1,
    [sym__init_declarator] = 1,
    [sym__direct_declarator] = 1,
    [aux_sym_function_definition_repeat1] = 1,
    [aux_sym_declaration_specifiers_repeat1] = 1,
    [aux_sym_type_name_repeat1] = 1,
    [aux_sym_struct_specifier_repeat1] = 1,
    [aux_sym_declaration_repeat1] = 1,
    [aux_sym_designation_repeat1] = 1,
    [aux_sym_declarator_repeat1] = 1,
    [aux_sym__direct_declarator_repeat1] = 1,
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
    [7] = 85,
    [8] = 88,
    [9] = 1,
    [10] = 89,
    [11] = 91,
    [12] = 1,
    [13] = 93,
    [14] = 94,
    [15] = 85,
    [16] = 85,
    [17] = 94,
    [18] = 85,
    [19] = 88,
    [20] = 96,
    [21] = 91,
    [22] = 85,
    [23] = 93,
    [24] = 94,
    [25] = 96,
    [26] = 85,
    [27] = 85,
    [28] = 94,
    [29] = 96,
    [30] = 85,
    [31] = 85,
    [32] = 85,
    [33] = 96,
    [34] = 94,
    [35] = 97,
    [36] = 85,
    [37] = 97,
    [38] = 99,
    [39] = 85,
    [40] = 85,
    [41] = 100,
    [42] = 102,
    [43] = 102,
    [44] = 99,
    [45] = 85,
    [46] = 100,
    [47] = 102,
    [48] = 102,
    [49] = 103,
    [50] = 113,
    [51] = 82,
    [52] = 85,
    [53] = 114,
    [54] = 100,
    [55] = 1,
    [56] = 102,
    [57] = 114,
    [58] = 100,
    [59] = 102,
    [60] = 114,
    [61] = 116,
    [62] = 116,
    [63] = 99,
    [64] = 85,
    [65] = 100,
    [66] = 116,
    [67] = 116,
    [68] = 103,
    [69] = 113,
    [70] = 114,
    [71] = 100,
    [72] = 116,
    [73] = 116,
    [74] = 117,
    [75] = 117,
    [76] = 119,
    [77] = 120,
    [78] = 120,
    [79] = 117,
    [80] = 117,
    [81] = 121,
    [82] = 121,
    [83] = 117,
    [84] = 100,
    [85] = 120,
    [86] = 119,
    [87] = 117,
    [88] = 120,
    [89] = 120,
    [90] = 121,
    [91] = 121,
    [92] = 121,
    [93] = 121,
    [94] = 100,
    [95] = 121,
    [96] = 121,
    [97] = 121,
    [98] = 100,
    [99] = 117,
    [100] = 85,
    [101] = 114,
    [102] = 117,
    [103] = 97,
    [104] = 97,
    [105] = 103,
    [106] = 113,
    [107] = 114,
    [108] = 100,
    [109] = 97,
    [110] = 97,
    [111] = 117,
    [112] = 99,
    [113] = 94,
    [114] = 96,
    [115] = 85,
    [116] = 88,
    [117] = 85,
    [118] = 122,
    [119] = 124,
    [120] = 126,
    [121] = 126,
    [122] = 99,
    [123] = 85,
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
    [138] = 93,
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
    [205] = 139,
    [206] = 96,
    [207] = 80,
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
    [224] = 141,
    [225] = 99,
    [226] = 85,
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
    [248] = 93,
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
    [266] = 93,
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
        [sym_identifier] = ACTIONS(SHIFT(7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
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
        [sym_identifier] = ACTIONS(SHIFT(7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(11)),
    },
    [4] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(260)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(260)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(261)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [5] = {
        [sym__init_declarator] = ACTIONS(SHIFT(118)),
        [sym_declarator] = ACTIONS(SHIFT(119)),
        [sym__direct_declarator] = ACTIONS(SHIFT(120)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(121)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(122)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(123)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [6] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
    },
    [7] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [8] = {
        [sym_identifier] = ACTIONS(SHIFT(117)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
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
    [10] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(116)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
    },
    [11] = {
        [sym_identifier] = ACTIONS(SHIFT(13)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(14)),
    },
    [12] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
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
    [13] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(113)),
    },
    [14] = {
        [sym__type_specifier] = ACTIONS(SHIFT(15)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_struct_declaration] = ACTIONS(SHIFT(17)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(20)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(22)),
    },
    [15] = {
        [sym_declarator] = ACTIONS(SHIFT(34)),
        [sym__direct_declarator] = ACTIONS(SHIFT(35)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(37)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(38)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(39)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [16] = {
        [sym_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
    },
    [17] = {
        [sym__type_specifier] = ACTIONS(SHIFT(15)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_struct_declaration] = ACTIONS(SHIFT(17)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(33)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 1)),
    },
    [18] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [19] = {
        [sym_identifier] = ACTIONS(SHIFT(32)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(31)),
    },
    [21] = {
        [sym_identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(24)),
    },
    [22] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
    },
    [23] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(28)),
    },
    [24] = {
        [sym__type_specifier] = ACTIONS(SHIFT(15)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_struct_declaration] = ACTIONS(SHIFT(17)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(25)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(26)),
    },
    [25] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(27)),
    },
    [26] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
    },
    [27] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
    },
    [28] = {
        [sym__type_specifier] = ACTIONS(SHIFT(15)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_struct_declaration] = ACTIONS(SHIFT(17)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(29)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(27)),
    },
    [29] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(30)),
    },
    [30] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
    },
    [31] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
    },
    [32] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_name, 2)),
    },
    [33] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 2)),
    },
    [34] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
    },
    [35] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(105)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(106)),
    },
    [36] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(112)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [37] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
    },
    [38] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(104)),
        [sym_identifier] = ACTIONS(SHIFT(37)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(39)),
    },
    [39] = {
        [sym_declarator] = ACTIONS(SHIFT(41)),
        [sym__direct_declarator] = ACTIONS(SHIFT(42)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [40] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_pointer, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_pointer, 1)),
    },
    [41] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(103)),
    },
    [42] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [43] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
    },
    [44] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(48)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(45)),
    },
    [45] = {
        [sym_declarator] = ACTIONS(SHIFT(46)),
        [sym__direct_declarator] = ACTIONS(SHIFT(42)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [46] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(47)),
    },
    [47] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
    },
    [48] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [49] = {
        [sym_expression] = ACTIONS(SHIFT(102)),
        [sym_math_expression] = ACTIONS(SHIFT(75)),
        [sym_call_expression] = ACTIONS(SHIFT(75)),
        [sym_string] = ACTIONS(SHIFT(75)),
        [sym_identifier] = ACTIONS(SHIFT(75)),
        [sym_number] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(47)),
    },
    [50] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(51)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(52)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(53)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(47)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [51] = {
        [sym__type_specifier] = ACTIONS(SHIFT(100)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
    },
    [52] = {
        [sym_declarator] = ACTIONS(SHIFT(60)),
        [sym__direct_declarator] = ACTIONS(SHIFT(61)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(62)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(63)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(64)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [53] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(54)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(55)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(56)),
    },
    [54] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(59)),
    },
    [55] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(51)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(52)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(57)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [56] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
    },
    [57] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(58)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(55)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__direct_declarator_repeat1, 2)),
    },
    [58] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__direct_declarator_repeat1, 3)),
    },
    [59] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
    },
    [60] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
    },
    [61] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(68)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(69)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [62] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
    },
    [63] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(67)),
        [sym_identifier] = ACTIONS(SHIFT(62)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(64)),
    },
    [64] = {
        [sym_declarator] = ACTIONS(SHIFT(65)),
        [sym__direct_declarator] = ACTIONS(SHIFT(42)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [65] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(66)),
    },
    [66] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
    },
    [67] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(68)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(69)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [68] = {
        [sym_expression] = ACTIONS(SHIFT(74)),
        [sym_math_expression] = ACTIONS(SHIFT(75)),
        [sym_call_expression] = ACTIONS(SHIFT(75)),
        [sym_string] = ACTIONS(SHIFT(75)),
        [sym_identifier] = ACTIONS(SHIFT(75)),
        [sym_number] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(66)),
    },
    [69] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(51)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(52)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(70)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(66)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [70] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(71)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(55)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(72)),
    },
    [71] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(73)),
    },
    [72] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
    },
    [73] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
    },
    [74] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(72)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(77)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(78)),
    },
    [75] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [76] = {
        [sym_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(82)),
        [sym_call_expression] = ACTIONS(SHIFT(82)),
        [sym_string] = ACTIONS(SHIFT(82)),
        [sym_identifier] = ACTIONS(SHIFT(82)),
        [sym_number] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(83)),
    },
    [77] = {
        [sym_expression] = ACTIONS(SHIFT(80)),
        [sym_math_expression] = ACTIONS(SHIFT(75)),
        [sym_call_expression] = ACTIONS(SHIFT(75)),
        [sym_string] = ACTIONS(SHIFT(75)),
        [sym_identifier] = ACTIONS(SHIFT(75)),
        [sym_number] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [sym_expression] = ACTIONS(SHIFT(79)),
        [sym_math_expression] = ACTIONS(SHIFT(75)),
        [sym_call_expression] = ACTIONS(SHIFT(75)),
        [sym_string] = ACTIONS(SHIFT(75)),
        [sym_identifier] = ACTIONS(SHIFT(75)),
        [sym_number] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(77)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [80] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [81] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(84)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(85)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(88)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(89)),
    },
    [82] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [83] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [84] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(99)),
    },
    [85] = {
        [sym_expression] = ACTIONS(SHIFT(97)),
        [sym_math_expression] = ACTIONS(SHIFT(82)),
        [sym_call_expression] = ACTIONS(SHIFT(82)),
        [sym_string] = ACTIONS(SHIFT(82)),
        [sym_identifier] = ACTIONS(SHIFT(82)),
        [sym_number] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [sym_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(82)),
        [sym_call_expression] = ACTIONS(SHIFT(82)),
        [sym_string] = ACTIONS(SHIFT(82)),
        [sym_identifier] = ACTIONS(SHIFT(82)),
        [sym_number] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(93)),
    },
    [87] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [88] = {
        [sym_expression] = ACTIONS(SHIFT(91)),
        [sym_math_expression] = ACTIONS(SHIFT(82)),
        [sym_call_expression] = ACTIONS(SHIFT(82)),
        [sym_string] = ACTIONS(SHIFT(82)),
        [sym_identifier] = ACTIONS(SHIFT(82)),
        [sym_number] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [sym_expression] = ACTIONS(SHIFT(90)),
        [sym_math_expression] = ACTIONS(SHIFT(82)),
        [sym_call_expression] = ACTIONS(SHIFT(82)),
        [sym_string] = ACTIONS(SHIFT(82)),
        [sym_identifier] = ACTIONS(SHIFT(82)),
        [sym_number] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(88)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [91] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [92] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(94)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(85)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(95)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(88)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(89)),
    },
    [93] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [94] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(96)),
    },
    [95] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [96] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [97] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(98)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(85)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(88)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(89)),
    },
    [98] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
    },
    [99] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [100] = {
        [sym_declarator] = ACTIONS(SHIFT(101)),
        [sym__direct_declarator] = ACTIONS(SHIFT(61)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(62)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(63)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(64)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [101] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
    },
    [102] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(56)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(77)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(78)),
    },
    [103] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
    },
    [104] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(105)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(106)),
    },
    [105] = {
        [sym_expression] = ACTIONS(SHIFT(111)),
        [sym_math_expression] = ACTIONS(SHIFT(75)),
        [sym_call_expression] = ACTIONS(SHIFT(75)),
        [sym_string] = ACTIONS(SHIFT(75)),
        [sym_identifier] = ACTIONS(SHIFT(75)),
        [sym_number] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(103)),
    },
    [106] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(51)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(52)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(107)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(103)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [107] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(108)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(55)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(109)),
    },
    [108] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(110)),
    },
    [109] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
    },
    [110] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
    },
    [111] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(109)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(77)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(78)),
    },
    [112] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
    },
    [113] = {
        [sym__type_specifier] = ACTIONS(SHIFT(15)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_struct_declaration] = ACTIONS(SHIFT(17)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(114)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(31)),
    },
    [114] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(115)),
    },
    [115] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
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
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_name, 2)),
    },
    [118] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(257)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(258)),
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
        [sym_identifier] = ACTIONS(SHIFT(7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(138)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
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
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(127)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(128)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declarator, 1)),
    },
    [121] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
    },
    [122] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(126)),
        [sym_identifier] = ACTIONS(SHIFT(121)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(123)),
    },
    [123] = {
        [sym_declarator] = ACTIONS(SHIFT(124)),
        [sym__direct_declarator] = ACTIONS(SHIFT(42)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [124] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(125)),
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
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
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
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
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
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(127)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(128)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym_declarator, 2)),
    },
    [127] = {
        [sym_expression] = ACTIONS(SHIFT(133)),
        [sym_math_expression] = ACTIONS(SHIFT(75)),
        [sym_call_expression] = ACTIONS(SHIFT(75)),
        [sym_string] = ACTIONS(SHIFT(75)),
        [sym_identifier] = ACTIONS(SHIFT(75)),
        [sym_number] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(125)),
    },
    [128] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(51)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(52)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(129)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(125)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [129] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(130)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(55)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(131)),
    },
    [130] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(132)),
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
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
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
        [sym_identifier] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_typedef] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_extern] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_static] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_auto] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_register] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_const] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_restrict] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_volatile] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
    },
    [133] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(131)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(77)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(78)),
    },
    [134] = {
        [sym__type_specifier] = ACTIONS(SHIFT(253)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_identifier] = ACTIONS(SHIFT(7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(11)),
    },
    [135] = {
        [sym__init_declarator] = ACTIONS(SHIFT(249)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(225)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
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
        [sym_identifier] = ACTIONS(SHIFT(7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(248)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [137] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [sym_compound_statement] = ACTIONS(SHIFT(247)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(139)),
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
        [sym_string] = ACTIONS(SHIFT(203)),
        [sym_identifier] = ACTIONS(SHIFT(205)),
        [sym_number] = ACTIONS(SHIFT(203)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(206)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(207)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [140] = {
        [sym_initializer] = ACTIONS(SHIFT(141)),
        [sym_expression] = ACTIONS(SHIFT(142)),
        [sym_math_expression] = ACTIONS(SHIFT(143)),
        [sym_call_expression] = ACTIONS(SHIFT(143)),
        [sym_string] = ACTIONS(SHIFT(143)),
        [sym_identifier] = ACTIONS(SHIFT(143)),
        [sym_number] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(144)),
    },
    [141] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 3)),
    },
    [142] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(189)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(190)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(191)),
    },
    [143] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [144] = {
        [sym_initializer] = ACTIONS(SHIFT(145)),
        [sym_initializer_list] = ACTIONS(SHIFT(146)),
        [sym_designation] = ACTIONS(SHIFT(147)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(150)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(151)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(152)),
    },
    [145] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
    },
    [146] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(186)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(187)),
    },
    [147] = {
        [sym_initializer] = ACTIONS(SHIFT(185)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(150)),
    },
    [148] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(175)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(176)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(177)),
    },
    [149] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [150] = {
        [sym_initializer] = ACTIONS(SHIFT(145)),
        [sym_initializer_list] = ACTIONS(SHIFT(168)),
        [sym_designation] = ACTIONS(SHIFT(147)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(150)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(151)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(152)),
    },
    [151] = {
        [sym_expression] = ACTIONS(SHIFT(164)),
        [sym_math_expression] = ACTIONS(SHIFT(75)),
        [sym_call_expression] = ACTIONS(SHIFT(75)),
        [sym_string] = ACTIONS(SHIFT(75)),
        [sym_identifier] = ACTIONS(SHIFT(75)),
        [sym_number] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [sym_identifier] = ACTIONS(SHIFT(153)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(154)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(155)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(156)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(157)),
    },
    [154] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(163)),
    },
    [155] = {
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
    [156] = {
        [sym_expression] = ACTIONS(SHIFT(160)),
        [sym_math_expression] = ACTIONS(SHIFT(75)),
        [sym_call_expression] = ACTIONS(SHIFT(75)),
        [sym_string] = ACTIONS(SHIFT(75)),
        [sym_identifier] = ACTIONS(SHIFT(75)),
        [sym_number] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [sym_identifier] = ACTIONS(SHIFT(158)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(159)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(156)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(157)),
    },
    [159] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
    },
    [160] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(161)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(77)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(78)),
    },
    [161] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(162)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(156)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(157)),
    },
    [162] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
    },
    [163] = {
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
    [164] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(165)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(77)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(78)),
    },
    [165] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(166)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(163)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(156)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(157)),
    },
    [166] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(167)),
    },
    [167] = {
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
    [168] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(169)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(170)),
    },
    [169] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
    },
    [170] = {
        [sym_initializer] = ACTIONS(SHIFT(171)),
        [sym_designation] = ACTIONS(SHIFT(172)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(150)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(173)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(151)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(152)),
    },
    [171] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
    },
    [172] = {
        [sym_initializer] = ACTIONS(SHIFT(174)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(150)),
    },
    [173] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
    },
    [174] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
    },
    [175] = {
        [sym_expression] = ACTIONS(SHIFT(180)),
        [sym_math_expression] = ACTIONS(SHIFT(82)),
        [sym_call_expression] = ACTIONS(SHIFT(82)),
        [sym_string] = ACTIONS(SHIFT(82)),
        [sym_identifier] = ACTIONS(SHIFT(82)),
        [sym_number] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(181)),
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
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(175)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(176)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [179] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(175)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [180] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(182)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(85)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(183)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(88)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(89)),
    },
    [181] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [182] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(184)),
    },
    [183] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [184] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [185] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
    },
    [186] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
    },
    [187] = {
        [sym_initializer] = ACTIONS(SHIFT(171)),
        [sym_designation] = ACTIONS(SHIFT(172)),
        [sym_expression] = ACTIONS(SHIFT(148)),
        [sym_math_expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(149)),
        [sym_string] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(149)),
        [sym_number] = ACTIONS(SHIFT(149)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(150)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(188)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(151)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(152)),
    },
    [188] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
    },
    [189] = {
        [sym_expression] = ACTIONS(SHIFT(194)),
        [sym_math_expression] = ACTIONS(SHIFT(82)),
        [sym_call_expression] = ACTIONS(SHIFT(82)),
        [sym_string] = ACTIONS(SHIFT(82)),
        [sym_identifier] = ACTIONS(SHIFT(82)),
        [sym_number] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(195)),
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
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(189)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(190)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [193] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(189)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [194] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(196)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(85)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(197)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(88)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(89)),
    },
    [195] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [196] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(198)),
    },
    [197] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [198] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [199] = {
        [sym__type_specifier] = ACTIONS(SHIFT(243)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_identifier] = ACTIONS(SHIFT(7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(11)),
    },
    [200] = {
        [sym__init_declarator] = ACTIONS(SHIFT(221)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(225)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
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
        [sym_string] = ACTIONS(SHIFT(203)),
        [sym_identifier] = ACTIONS(SHIFT(205)),
        [sym_number] = ACTIONS(SHIFT(203)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(220)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [202] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(209)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(210)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(211)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(212)),
    },
    [203] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
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
        [sym_string] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym_statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_statement, 1)),
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
    [205] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1), REDUCE(sym_expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_name, 1), REDUCE(sym_expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
    },
    [206] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(208)),
    },
    [207] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 2)),
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
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
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
    [210] = {
        [sym_expression] = ACTIONS(SHIFT(215)),
        [sym_math_expression] = ACTIONS(SHIFT(82)),
        [sym_call_expression] = ACTIONS(SHIFT(82)),
        [sym_string] = ACTIONS(SHIFT(82)),
        [sym_identifier] = ACTIONS(SHIFT(82)),
        [sym_number] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(216)),
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
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(210)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(211)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [214] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(210)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
    },
    [215] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(217)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(85)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(218)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(88)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(89)),
    },
    [216] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [217] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(219)),
    },
    [218] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [219] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [220] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
    },
    [221] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(237)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(239)),
    },
    [222] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(140)),
    },
    [223] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(230)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(231)),
    },
    [224] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
    },
    [225] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(229)),
        [sym_identifier] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(226)),
    },
    [226] = {
        [sym_declarator] = ACTIONS(SHIFT(227)),
        [sym__direct_declarator] = ACTIONS(SHIFT(42)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(44)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(45)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [227] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(228)),
    },
    [228] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
    },
    [229] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(230)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(231)),
    },
    [230] = {
        [sym_expression] = ACTIONS(SHIFT(236)),
        [sym_math_expression] = ACTIONS(SHIFT(75)),
        [sym_call_expression] = ACTIONS(SHIFT(75)),
        [sym_string] = ACTIONS(SHIFT(75)),
        [sym_identifier] = ACTIONS(SHIFT(75)),
        [sym_number] = ACTIONS(SHIFT(75)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(228)),
    },
    [231] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(51)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(52)),
        [sym_type_name] = ACTIONS(SHIFT(16)),
        [sym_struct_specifier] = ACTIONS(SHIFT(16)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(232)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(19)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(21)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(228)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [232] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(233)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(55)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(234)),
    },
    [233] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(235)),
    },
    [234] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
    },
    [235] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
    },
    [236] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(234)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(77)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(78)),
    },
    [237] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(242)),
    },
    [238] = {
        [sym__init_declarator] = ACTIONS(SHIFT(240)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(225)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
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
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
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
    [240] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(241)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
    },
    [241] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
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
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
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
    [243] = {
        [sym__init_declarator] = ACTIONS(SHIFT(244)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(225)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [244] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(245)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(242)),
    },
    [245] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(246)),
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
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
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
    [247] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
    },
    [249] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(250)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(251)),
    },
    [250] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(252)),
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
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
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
    [252] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
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
    [253] = {
        [sym__init_declarator] = ACTIONS(SHIFT(254)),
        [sym_declarator] = ACTIONS(SHIFT(222)),
        [sym__direct_declarator] = ACTIONS(SHIFT(223)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(225)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [254] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(255)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(252)),
    },
    [255] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(256)),
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
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
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
    [257] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(259)),
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
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(262)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [261] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_declaration_specifiers, 2)),
    },
    [262] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_type_name] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
    },
    [263] = {
        [sym__init_declarator] = ACTIONS(SHIFT(264)),
        [sym_declarator] = ACTIONS(SHIFT(265)),
        [sym__direct_declarator] = ACTIONS(SHIFT(120)),
        [sym_pointer] = ACTIONS(SHIFT(36)),
        [sym_identifier] = ACTIONS(SHIFT(121)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(122)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(123)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(40)),
    },
    [264] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(268)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(238)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(259)),
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
        [sym_identifier] = ACTIONS(SHIFT(7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(266)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_STR_typedef] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_extern] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_static] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_auto] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_register] = ACTIONS(SHIFT(9)),
        [aux_sym_STR_signed] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_unsigned] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_long] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_short] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_const] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_restrict] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_volatile] = ACTIONS(SHIFT(12)),
    },
    [266] = {
        [sym_compound_statement] = ACTIONS(SHIFT(267)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(139)),
    },
    [267] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [268] = {
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(269)),
    },
    [269] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
