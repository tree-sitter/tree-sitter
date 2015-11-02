#include "tree_sitter/parser.h"

#define STATE_COUNT 268
#define SYMBOL_COUNT 70

enum {
    sym_program = ts_builtin_sym_start,
    sym_preproc_define,
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
    aux_sym_program_repeat1,
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
    anon_sym_POUNDdefine,
    aux_sym_SLASH_LPAREN_BSLASH_LF_PIPE_DOT_RPAREN_STAR_SLASH,
    anon_sym_LF,
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
    [sym_preproc_define] = "preproc_define",
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
    [aux_sym_program_repeat1] = "program_repeat1",
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
    [anon_sym_POUNDdefine] = "#define",
    [aux_sym_SLASH_LPAREN_BSLASH_LF_PIPE_DOT_RPAREN_STAR_SLASH] = "/(\\n|.)*/",
    [anon_sym_LF] = "\n",
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
    [sym_preproc_define] = TSNodeTypeNamed,
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
    [aux_sym_program_repeat1] = TSNodeTypeHidden,
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
    [anon_sym_POUNDdefine] = TSNodeTypeAnonymous,
    [aux_sym_SLASH_LPAREN_BSLASH_LF_PIPE_DOT_RPAREN_STAR_SLASH] = TSNodeTypeHidden,
    [anon_sym_LF] = TSNodeTypeAnonymous,
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
                ADVANCE(12);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
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
            if (lookahead == '/')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(11);
            ACCEPT_TOKEN(sym_comment);
        case 12:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(sym_identifier);
        case 13:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'u')
                ADVANCE(14);
            ACCEPT_TOKEN(sym_identifier);
        case 14:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(15);
            ACCEPT_TOKEN(sym_identifier);
        case 15:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'o')
                ADVANCE(16);
            ACCEPT_TOKEN(sym_identifier);
        case 16:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_auto);
        case 17:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'o')
                ADVANCE(18);
            ACCEPT_TOKEN(sym_identifier);
        case 18:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'n')
                ADVANCE(19);
            ACCEPT_TOKEN(sym_identifier);
        case 19:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 's')
                ADVANCE(20);
            ACCEPT_TOKEN(sym_identifier);
        case 20:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(21);
            ACCEPT_TOKEN(sym_identifier);
        case 21:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_const);
        case 22:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'w') ||
                (lookahead == 'y') ||
                (lookahead == 'z'))
                ADVANCE(12);
            if (lookahead == 'x')
                ADVANCE(23);
            ACCEPT_TOKEN(sym_identifier);
        case 23:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(24);
            ACCEPT_TOKEN(sym_identifier);
        case 24:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(25);
            ACCEPT_TOKEN(sym_identifier);
        case 25:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'r')
                ADVANCE(26);
            ACCEPT_TOKEN(sym_identifier);
        case 26:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'n')
                ADVANCE(27);
            ACCEPT_TOKEN(sym_identifier);
        case 27:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_extern);
        case 28:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'o')
                ADVANCE(29);
            ACCEPT_TOKEN(sym_identifier);
        case 29:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'n')
                ADVANCE(30);
            ACCEPT_TOKEN(sym_identifier);
        case 30:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'g')
                ADVANCE(31);
            ACCEPT_TOKEN(sym_identifier);
        case 31:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_long);
        case 32:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(33);
            ACCEPT_TOKEN(sym_identifier);
        case 33:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'g')
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(40);
            ACCEPT_TOKEN(sym_identifier);
        case 34:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'i')
                ADVANCE(35);
            ACCEPT_TOKEN(sym_identifier);
        case 35:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 's')
                ADVANCE(36);
            ACCEPT_TOKEN(sym_identifier);
        case 36:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(37);
            ACCEPT_TOKEN(sym_identifier);
        case 37:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(38);
            ACCEPT_TOKEN(sym_identifier);
        case 38:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'r')
                ADVANCE(39);
            ACCEPT_TOKEN(sym_identifier);
        case 39:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_register);
        case 40:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(41);
            ACCEPT_TOKEN(sym_identifier);
        case 41:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'r')
                ADVANCE(42);
            ACCEPT_TOKEN(sym_identifier);
        case 42:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'i')
                ADVANCE(43);
            ACCEPT_TOKEN(sym_identifier);
        case 43:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(44);
            ACCEPT_TOKEN(sym_identifier);
        case 44:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(45);
            ACCEPT_TOKEN(sym_identifier);
        case 45:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_restrict);
        case 46:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'h')
                ADVANCE(47);
            if (lookahead == 'i')
                ADVANCE(51);
            if (lookahead == 't')
                ADVANCE(56);
            ACCEPT_TOKEN(sym_identifier);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'o')
                ADVANCE(48);
            ACCEPT_TOKEN(sym_identifier);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'r')
                ADVANCE(49);
            ACCEPT_TOKEN(sym_identifier);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(50);
            ACCEPT_TOKEN(sym_identifier);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_short);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'g')
                ADVANCE(52);
            ACCEPT_TOKEN(sym_identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'n')
                ADVANCE(53);
            ACCEPT_TOKEN(sym_identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(54);
            ACCEPT_TOKEN(sym_identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'd')
                ADVANCE(55);
            ACCEPT_TOKEN(sym_identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_signed);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'a')
                ADVANCE(57);
            if (lookahead == 'r')
                ADVANCE(61);
            ACCEPT_TOKEN(sym_identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(58);
            ACCEPT_TOKEN(sym_identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'i')
                ADVANCE(59);
            ACCEPT_TOKEN(sym_identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(60);
            ACCEPT_TOKEN(sym_identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_static);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'u')
                ADVANCE(62);
            ACCEPT_TOKEN(sym_identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'c')
                ADVANCE(63);
            ACCEPT_TOKEN(sym_identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(64);
            ACCEPT_TOKEN(sym_identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_struct);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(12);
            if (lookahead == 'y')
                ADVANCE(66);
            ACCEPT_TOKEN(sym_identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'p')
                ADVANCE(67);
            ACCEPT_TOKEN(sym_identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(68);
            ACCEPT_TOKEN(sym_identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'd')
                ADVANCE(69);
            ACCEPT_TOKEN(sym_identifier);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(70);
            ACCEPT_TOKEN(sym_identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'f')
                ADVANCE(71);
            ACCEPT_TOKEN(sym_identifier);
        case 71:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_typedef);
        case 72:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'n')
                ADVANCE(73);
            ACCEPT_TOKEN(sym_identifier);
        case 73:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 's')
                ADVANCE(74);
            ACCEPT_TOKEN(sym_identifier);
        case 74:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'i')
                ADVANCE(75);
            ACCEPT_TOKEN(sym_identifier);
        case 75:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'g')
                ADVANCE(76);
            ACCEPT_TOKEN(sym_identifier);
        case 76:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'n')
                ADVANCE(77);
            ACCEPT_TOKEN(sym_identifier);
        case 77:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(78);
            ACCEPT_TOKEN(sym_identifier);
        case 78:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'd')
                ADVANCE(79);
            ACCEPT_TOKEN(sym_identifier);
        case 79:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_unsigned);
        case 80:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'o')
                ADVANCE(81);
            ACCEPT_TOKEN(sym_identifier);
        case 81:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'l')
                ADVANCE(82);
            ACCEPT_TOKEN(sym_identifier);
        case 82:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'a')
                ADVANCE(83);
            ACCEPT_TOKEN(sym_identifier);
        case 83:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 't')
                ADVANCE(84);
            ACCEPT_TOKEN(sym_identifier);
        case 84:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'i')
                ADVANCE(85);
            ACCEPT_TOKEN(sym_identifier);
        case 85:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'l')
                ADVANCE(86);
            ACCEPT_TOKEN(sym_identifier);
        case 86:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'e')
                ADVANCE(87);
            ACCEPT_TOKEN(sym_identifier);
        case 87:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            ACCEPT_TOKEN(anon_sym_volatile);
        case 88:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 89:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(89);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 's')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(72);
            LEX_ERROR();
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'h')
                ADVANCE(47);
            if (lookahead == 'i')
                ADVANCE(51);
            if (lookahead == 't')
                ADVANCE(91);
            ACCEPT_TOKEN(sym_identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'r')
                ADVANCE(61);
            ACCEPT_TOKEN(sym_identifier);
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
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
            LEX_ERROR();
        case 93:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            LEX_ERROR();
        case 94:
            ACCEPT_TOKEN(anon_sym_LPAREN);
        case 95:
            ACCEPT_TOKEN(anon_sym_STAR);
        case 96:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            LEX_ERROR();
        case 97:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 's')
                ADVANCE(98);
            if (lookahead == 'u')
                ADVANCE(72);
            LEX_ERROR();
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'h')
                ADVANCE(47);
            if (lookahead == 'i')
                ADVANCE(51);
            ACCEPT_TOKEN(sym_identifier);
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
                ADVANCE(12);
            if (lookahead == '{')
                ADVANCE(100);
            LEX_ERROR();
        case 100:
            ACCEPT_TOKEN(anon_sym_LBRACE);
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
                ADVANCE(12);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 's')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == '}')
                ADVANCE(102);
            LEX_ERROR();
        case 102:
            ACCEPT_TOKEN(anon_sym_RBRACE);
        case 103:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '{')
                ADVANCE(100);
            LEX_ERROR();
        case 104:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(102);
            LEX_ERROR();
        case 105:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == '[')
                ADVANCE(106);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 's')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == '}')
                ADVANCE(102);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(anon_sym_LBRACK);
        case 107:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 109:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 110:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(106);
            LEX_ERROR();
        case 111:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(111);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == ']')
                ADVANCE(119);
            LEX_ERROR();
        case 112:
            if (lookahead == '\"')
                ADVANCE(113);
            if (lookahead == '\\')
                ADVANCE(114);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(112);
            LEX_ERROR();
        case 113:
            ACCEPT_TOKEN(sym_string);
        case 114:
            if (lookahead == '\"')
                ADVANCE(115);
            if (lookahead == '\\')
                ADVANCE(114);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(112);
            LEX_ERROR();
        case 115:
            if (lookahead == '\"')
                ADVANCE(113);
            if (lookahead == '\\')
                ADVANCE(114);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(112);
            ACCEPT_TOKEN(sym_string);
        case 116:
            if (lookahead == '.')
                ADVANCE(117);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            ACCEPT_TOKEN(sym_number);
        case 117:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(118);
            LEX_ERROR();
        case 118:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(118);
            ACCEPT_TOKEN(sym_number);
        case 119:
            ACCEPT_TOKEN(anon_sym_RBRACK);
        case 120:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(120);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
            LEX_ERROR();
        case 121:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 122:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 123:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(123);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(106);
            LEX_ERROR();
        case 124:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(124);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '+')
                ADVANCE(125);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ']')
                ADVANCE(119);
            LEX_ERROR();
        case 125:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 126:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            LEX_ERROR();
        case 127:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            LEX_ERROR();
        case 128:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '+')
                ADVANCE(125);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 129:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
            if (lookahead == '\n')
                ADVANCE(137);
            if (lookahead == '/')
                ADVANCE(131);
            if (lookahead == '\\')
                ADVANCE(134);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(136);
            LEX_ERROR();
        case 130:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(131);
            if (lookahead == '\\')
                ADVANCE(134);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(136);
            ACCEPT_TOKEN(aux_sym_SLASH_LPAREN_BSLASH_LF_PIPE_DOT_RPAREN_STAR_SLASH);
        case 131:
            if (lookahead == '/')
                ADVANCE(132);
            if (lookahead == '\\')
                ADVANCE(134);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(136);
            ACCEPT_TOKEN(aux_sym_SLASH_LPAREN_BSLASH_LF_PIPE_DOT_RPAREN_STAR_SLASH);
        case 132:
            if (lookahead == '\\')
                ADVANCE(133);
            ACCEPT_TOKEN(sym_comment);
        case 133:
            if (lookahead == '\\')
                ADVANCE(133);
            ACCEPT_TOKEN(sym_comment);
        case 134:
            if (lookahead == '\n')
                ADVANCE(135);
            if (lookahead == '\\')
                ADVANCE(134);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(136);
            ACCEPT_TOKEN(aux_sym_SLASH_LPAREN_BSLASH_LF_PIPE_DOT_RPAREN_STAR_SLASH);
        case 135:
            if (lookahead == '\\')
                ADVANCE(134);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(136);
            ACCEPT_TOKEN(aux_sym_SLASH_LPAREN_BSLASH_LF_PIPE_DOT_RPAREN_STAR_SLASH);
        case 136:
            if (lookahead == '\\')
                ADVANCE(134);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(136);
            ACCEPT_TOKEN(aux_sym_SLASH_LPAREN_BSLASH_LF_PIPE_DOT_RPAREN_STAR_SLASH);
        case 137:
            START_TOKEN();
            if (lookahead == '\\')
                ADVANCE(134);
            ACCEPT_TOKEN(anon_sym_LF);
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == '\n')
                ADVANCE(139);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if (lookahead == '/')
                ADVANCE(10);
            ACCEPT_TOKEN(anon_sym_LF);
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(141);
            LEX_ERROR();
        case 141:
            ACCEPT_TOKEN(anon_sym_SEMI);
        case 142:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(141);
            if (lookahead == '=')
                ADVANCE(143);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
            if (lookahead == '{')
                ADVANCE(100);
            LEX_ERROR();
        case 143:
            ACCEPT_TOKEN(anon_sym_EQ);
        case 144:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(141);
            if (lookahead == '=')
                ADVANCE(143);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == '[')
                ADVANCE(106);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
            if (lookahead == '{')
                ADVANCE(100);
            LEX_ERROR();
        case 145:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(145);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
            if (lookahead == '{')
                ADVANCE(100);
            LEX_ERROR();
        case 146:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
            if (lookahead == '}')
                ADVANCE(102);
            LEX_ERROR();
        case 147:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(147);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == '{')
                ADVANCE(100);
            LEX_ERROR();
        case 148:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '+')
                ADVANCE(125);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(141);
            LEX_ERROR();
        case 149:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == '.')
                ADVANCE(150);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == '[')
                ADVANCE(106);
            if (lookahead == '{')
                ADVANCE(100);
            LEX_ERROR();
        case 150:
            ACCEPT_TOKEN(anon_sym_DOT);
        case 151:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(151);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(102);
            LEX_ERROR();
        case 152:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(152);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '+')
                ADVANCE(125);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(102);
            LEX_ERROR();
        case 153:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(153);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(143);
            LEX_ERROR();
        case 154:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(154);
            if (lookahead == '.')
                ADVANCE(150);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(143);
            if (lookahead == '[')
                ADVANCE(106);
            LEX_ERROR();
        case 155:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(155);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == '.')
                ADVANCE(150);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == '[')
                ADVANCE(106);
            if (lookahead == '{')
                ADVANCE(100);
            if (lookahead == '}')
                ADVANCE(102);
            LEX_ERROR();
        case 156:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(156);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '+')
                ADVANCE(125);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(141);
            LEX_ERROR();
        case 157:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(157);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '+')
                ADVANCE(125);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(141);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            LEX_ERROR();
        case 158:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(158);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(141);
            if (lookahead == '=')
                ADVANCE(143);
            LEX_ERROR();
        case 159:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(141);
            if (lookahead == '=')
                ADVANCE(143);
            if (lookahead == '[')
                ADVANCE(106);
            LEX_ERROR();
        case 160:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(160);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(141);
            LEX_ERROR();
        case 161:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(161);
            if (lookahead == '\n')
                ADVANCE(162);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == '#')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '+')
                ADVANCE(125);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '.')
                ADVANCE(150);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (lookahead == ';')
                ADVANCE(141);
            if (lookahead == '=')
                ADVANCE(143);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == '[')
                ADVANCE(106);
            if (lookahead == ']')
                ADVANCE(119);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
            if (lookahead == '{')
                ADVANCE(100);
            if (lookahead == '}')
                ADVANCE(102);
            LEX_ERROR();
        case 162:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == '#')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '+')
                ADVANCE(125);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '.')
                ADVANCE(150);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (lookahead == ';')
                ADVANCE(141);
            if (lookahead == '=')
                ADVANCE(143);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == '[')
                ADVANCE(106);
            if (lookahead == ']')
                ADVANCE(119);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
            if (lookahead == '{')
                ADVANCE(100);
            if (lookahead == '}')
                ADVANCE(102);
            ACCEPT_TOKEN(anon_sym_LF);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(161);
            if (lookahead == '\n')
                ADVANCE(162);
            if (lookahead == '\"')
                ADVANCE(112);
            if (lookahead == '#')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(94);
            if (lookahead == ')')
                ADVANCE(109);
            if (lookahead == '*')
                ADVANCE(95);
            if (lookahead == '+')
                ADVANCE(125);
            if (lookahead == ',')
                ADVANCE(122);
            if (lookahead == '.')
                ADVANCE(150);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(116);
            if (lookahead == ';')
                ADVANCE(141);
            if (lookahead == '=')
                ADVANCE(143);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            if (lookahead == '[')
                ADVANCE(106);
            if (lookahead == ']')
                ADVANCE(119);
            if (lookahead == 'a')
                ADVANCE(13);
            if (lookahead == 'c')
                ADVANCE(17);
            if (lookahead == 'e')
                ADVANCE(22);
            if (lookahead == 'l')
                ADVANCE(28);
            if (lookahead == 'r')
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(46);
            if (lookahead == 't')
                ADVANCE(65);
            if (lookahead == 'u')
                ADVANCE(72);
            if (lookahead == 'v')
                ADVANCE(80);
            if (lookahead == '{')
                ADVANCE(100);
            if (lookahead == '}')
                ADVANCE(102);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 88,
    [2] = 1,
    [3] = 89,
    [4] = 92,
    [5] = 93,
    [6] = 93,
    [7] = 88,
    [8] = 89,
    [9] = 96,
    [10] = 96,
    [11] = 92,
    [12] = 97,
    [13] = 99,
    [14] = 92,
    [15] = 93,
    [16] = 101,
    [17] = 103,
    [18] = 101,
    [19] = 93,
    [20] = 93,
    [21] = 101,
    [22] = 96,
    [23] = 104,
    [24] = 99,
    [25] = 93,
    [26] = 93,
    [27] = 101,
    [28] = 103,
    [29] = 101,
    [30] = 104,
    [31] = 93,
    [32] = 93,
    [33] = 104,
    [34] = 93,
    [35] = 93,
    [36] = 93,
    [37] = 104,
    [38] = 101,
    [39] = 105,
    [40] = 93,
    [41] = 107,
    [42] = 93,
    [43] = 93,
    [44] = 105,
    [45] = 108,
    [46] = 110,
    [47] = 107,
    [48] = 93,
    [49] = 110,
    [50] = 108,
    [51] = 110,
    [52] = 110,
    [53] = 111,
    [54] = 120,
    [55] = 89,
    [56] = 93,
    [57] = 121,
    [58] = 108,
    [59] = 92,
    [60] = 110,
    [61] = 121,
    [62] = 108,
    [63] = 110,
    [64] = 121,
    [65] = 123,
    [66] = 107,
    [67] = 93,
    [68] = 123,
    [69] = 108,
    [70] = 123,
    [71] = 123,
    [72] = 111,
    [73] = 120,
    [74] = 121,
    [75] = 108,
    [76] = 123,
    [77] = 123,
    [78] = 124,
    [79] = 124,
    [80] = 126,
    [81] = 127,
    [82] = 127,
    [83] = 124,
    [84] = 124,
    [85] = 128,
    [86] = 128,
    [87] = 124,
    [88] = 108,
    [89] = 127,
    [90] = 126,
    [91] = 124,
    [92] = 127,
    [93] = 127,
    [94] = 128,
    [95] = 128,
    [96] = 128,
    [97] = 128,
    [98] = 108,
    [99] = 128,
    [100] = 128,
    [101] = 128,
    [102] = 108,
    [103] = 124,
    [104] = 93,
    [105] = 121,
    [106] = 124,
    [107] = 105,
    [108] = 105,
    [109] = 111,
    [110] = 120,
    [111] = 121,
    [112] = 108,
    [113] = 105,
    [114] = 105,
    [115] = 124,
    [116] = 107,
    [117] = 104,
    [118] = 93,
    [119] = 96,
    [120] = 129,
    [121] = 138,
    [122] = 1,
    [123] = 1,
    [124] = 93,
    [125] = 140,
    [126] = 142,
    [127] = 144,
    [128] = 107,
    [129] = 93,
    [130] = 144,
    [131] = 108,
    [132] = 144,
    [133] = 144,
    [134] = 111,
    [135] = 120,
    [136] = 121,
    [137] = 108,
    [138] = 144,
    [139] = 144,
    [140] = 124,
    [141] = 89,
    [142] = 93,
    [143] = 145,
    [144] = 1,
    [145] = 103,
    [146] = 146,
    [147] = 147,
    [148] = 140,
    [149] = 148,
    [150] = 148,
    [151] = 149,
    [152] = 151,
    [153] = 151,
    [154] = 147,
    [155] = 152,
    [156] = 152,
    [157] = 153,
    [158] = 149,
    [159] = 127,
    [160] = 96,
    [161] = 154,
    [162] = 153,
    [163] = 124,
    [164] = 154,
    [165] = 153,
    [166] = 151,
    [167] = 151,
    [168] = 155,
    [169] = 151,
    [170] = 147,
    [171] = 151,
    [172] = 151,
    [173] = 147,
    [174] = 126,
    [175] = 127,
    [176] = 127,
    [177] = 152,
    [178] = 152,
    [179] = 128,
    [180] = 152,
    [181] = 108,
    [182] = 152,
    [183] = 152,
    [184] = 151,
    [185] = 140,
    [186] = 155,
    [187] = 140,
    [188] = 126,
    [189] = 127,
    [190] = 127,
    [191] = 148,
    [192] = 148,
    [193] = 128,
    [194] = 148,
    [195] = 108,
    [196] = 148,
    [197] = 148,
    [198] = 89,
    [199] = 93,
    [200] = 146,
    [201] = 156,
    [202] = 156,
    [203] = 146,
    [204] = 104,
    [205] = 1,
    [206] = 157,
    [207] = 1,
    [208] = 146,
    [209] = 126,
    [210] = 127,
    [211] = 127,
    [212] = 156,
    [213] = 156,
    [214] = 128,
    [215] = 156,
    [216] = 108,
    [217] = 156,
    [218] = 156,
    [219] = 104,
    [220] = 140,
    [221] = 158,
    [222] = 159,
    [223] = 107,
    [224] = 93,
    [225] = 159,
    [226] = 108,
    [227] = 159,
    [228] = 159,
    [229] = 111,
    [230] = 120,
    [231] = 121,
    [232] = 108,
    [233] = 159,
    [234] = 159,
    [235] = 124,
    [236] = 160,
    [237] = 93,
    [238] = 146,
    [239] = 140,
    [240] = 160,
    [241] = 146,
    [242] = 93,
    [243] = 140,
    [244] = 160,
    [245] = 146,
    [246] = 1,
    [247] = 103,
    [248] = 140,
    [249] = 160,
    [250] = 145,
    [251] = 145,
    [252] = 93,
    [253] = 140,
    [254] = 160,
    [255] = 145,
    [256] = 160,
    [257] = 1,
    [258] = 1,
    [259] = 89,
    [260] = 93,
    [261] = 140,
    [262] = 142,
    [263] = 103,
    [264] = 1,
    [265] = 160,
    [266] = 1,
    [267] = 88,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction *ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = ACTIONS(SHIFT(1)),
        [sym_preproc_define] = ACTIONS(SHIFT(2)),
        [sym_function_definition] = ACTIONS(SHIFT(2)),
        [sym_declaration_specifiers] = ACTIONS(SHIFT(3)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(5)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(2)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_program_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 0)),
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
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(2)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_program_repeat1] = ACTIONS(SHIFT(267)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
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
        [sym__type_specifier] = ACTIONS(SHIFT(260)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
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
        [sym_type_name] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(259)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
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
        [sym__init_declarator] = ACTIONS(SHIFT(125)),
        [sym_declarator] = ACTIONS(SHIFT(126)),
        [sym__direct_declarator] = ACTIONS(SHIFT(127)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(128)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(129)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(130)),
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
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
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
    [9] = {
        [sym_identifier] = ACTIONS(SHIFT(124)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [sym_identifier] = ACTIONS(SHIFT(120)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
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
    [12] = {
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(119)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(17)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
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
    [15] = {
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
    [16] = {
        [sym__type_specifier] = ACTIONS(SHIFT(19)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_struct_declaration] = ACTIONS(SHIFT(21)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(117)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(118)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [sym__type_specifier] = ACTIONS(SHIFT(19)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_struct_declaration] = ACTIONS(SHIFT(21)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(23)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(25)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [sym_declarator] = ACTIONS(SHIFT(38)),
        [sym__direct_declarator] = ACTIONS(SHIFT(39)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(42)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(44)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [sym_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [sym__type_specifier] = ACTIONS(SHIFT(19)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_struct_declaration] = ACTIONS(SHIFT(21)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(37)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(27)),
        [sym_identifier] = ACTIONS(SHIFT(28)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
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
    [26] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [sym__type_specifier] = ACTIONS(SHIFT(19)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_struct_declaration] = ACTIONS(SHIFT(21)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(33)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(29)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [sym__type_specifier] = ACTIONS(SHIFT(19)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_struct_declaration] = ACTIONS(SHIFT(21)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(30)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(31)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(32)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [33] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(31)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [34] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [35] = {
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
    [36] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_pointer] = ACTIONS(REDUCE(sym_type_name, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [37] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [38] = {
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
    [39] = {
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
        [anon_sym_LBRACK] = ACTIONS(SHIFT(109)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(110)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [40] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(116)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [41] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(42)),
        [sym_identifier] = ACTIONS(SHIFT(44)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [42] = {
        [sym_declarator] = ACTIONS(SHIFT(45)),
        [sym__direct_declarator] = ACTIONS(SHIFT(46)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(47)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(48)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [43] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_pointer] = ACTIONS(REDUCE(sym_pointer, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [44] = {
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
    [45] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(107)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [46] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(53)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(54)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [47] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(52)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(48)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [48] = {
        [sym_declarator] = ACTIONS(SHIFT(50)),
        [sym__direct_declarator] = ACTIONS(SHIFT(46)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(47)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(48)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [49] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [50] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(51)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [51] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [52] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(53)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(54)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [53] = {
        [sym_expression] = ACTIONS(SHIFT(106)),
        [sym_math_expression] = ACTIONS(SHIFT(79)),
        [sym_call_expression] = ACTIONS(SHIFT(79)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(51)),
        [sym_string] = ACTIONS(SHIFT(79)),
        [sym_identifier] = ACTIONS(SHIFT(79)),
        [sym_number] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [54] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(55)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(56)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(57)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(51)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [55] = {
        [sym__type_specifier] = ACTIONS(SHIFT(104)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [56] = {
        [sym_declarator] = ACTIONS(SHIFT(64)),
        [sym__direct_declarator] = ACTIONS(SHIFT(65)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(66)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(67)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(68)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [57] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(58)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(60)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [58] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(63)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [59] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(55)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(56)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(61)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [60] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [61] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(62)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__direct_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [62] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__direct_declarator_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [63] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [64] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [65] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(72)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(73)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [66] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(71)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(67)),
        [sym_identifier] = ACTIONS(SHIFT(68)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [67] = {
        [sym_declarator] = ACTIONS(SHIFT(69)),
        [sym__direct_declarator] = ACTIONS(SHIFT(46)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(47)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(48)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [68] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [69] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(70)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [70] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [71] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(72)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(73)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [72] = {
        [sym_expression] = ACTIONS(SHIFT(78)),
        [sym_math_expression] = ACTIONS(SHIFT(79)),
        [sym_call_expression] = ACTIONS(SHIFT(79)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(70)),
        [sym_string] = ACTIONS(SHIFT(79)),
        [sym_identifier] = ACTIONS(SHIFT(79)),
        [sym_number] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(55)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(56)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(74)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(75)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [75] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(77)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(76)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [80] = {
        [sym_expression] = ACTIONS(SHIFT(85)),
        [sym_math_expression] = ACTIONS(SHIFT(86)),
        [sym_call_expression] = ACTIONS(SHIFT(86)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(87)),
        [sym_string] = ACTIONS(SHIFT(86)),
        [sym_identifier] = ACTIONS(SHIFT(86)),
        [sym_number] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [sym_expression] = ACTIONS(SHIFT(84)),
        [sym_math_expression] = ACTIONS(SHIFT(79)),
        [sym_call_expression] = ACTIONS(SHIFT(79)),
        [sym_string] = ACTIONS(SHIFT(79)),
        [sym_identifier] = ACTIONS(SHIFT(79)),
        [sym_number] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [82] = {
        [sym_expression] = ACTIONS(SHIFT(83)),
        [sym_math_expression] = ACTIONS(SHIFT(79)),
        [sym_call_expression] = ACTIONS(SHIFT(79)),
        [sym_string] = ACTIONS(SHIFT(79)),
        [sym_identifier] = ACTIONS(SHIFT(79)),
        [sym_number] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(88)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(89)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(91)),
        [anon_sym_STAR] = ACTIONS(SHIFT(92)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(103)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [sym_expression] = ACTIONS(SHIFT(101)),
        [sym_math_expression] = ACTIONS(SHIFT(86)),
        [sym_call_expression] = ACTIONS(SHIFT(86)),
        [sym_string] = ACTIONS(SHIFT(86)),
        [sym_identifier] = ACTIONS(SHIFT(86)),
        [sym_number] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [sym_expression] = ACTIONS(SHIFT(96)),
        [sym_math_expression] = ACTIONS(SHIFT(86)),
        [sym_call_expression] = ACTIONS(SHIFT(86)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(97)),
        [sym_string] = ACTIONS(SHIFT(86)),
        [sym_identifier] = ACTIONS(SHIFT(86)),
        [sym_number] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [sym_expression] = ACTIONS(SHIFT(95)),
        [sym_math_expression] = ACTIONS(SHIFT(86)),
        [sym_call_expression] = ACTIONS(SHIFT(86)),
        [sym_string] = ACTIONS(SHIFT(86)),
        [sym_identifier] = ACTIONS(SHIFT(86)),
        [sym_number] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [sym_expression] = ACTIONS(SHIFT(94)),
        [sym_math_expression] = ACTIONS(SHIFT(86)),
        [sym_call_expression] = ACTIONS(SHIFT(86)),
        [sym_string] = ACTIONS(SHIFT(86)),
        [sym_identifier] = ACTIONS(SHIFT(86)),
        [sym_number] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(92)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(98)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(89)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_STAR] = ACTIONS(SHIFT(92)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(100)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [99] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(102)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(89)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(92)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [103] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [sym_declarator] = ACTIONS(SHIFT(105)),
        [sym__direct_declarator] = ACTIONS(SHIFT(65)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(66)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(67)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(68)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [106] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(60)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [107] = {
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
    [108] = {
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
        [anon_sym_LBRACK] = ACTIONS(SHIFT(109)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(110)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [sym_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(79)),
        [sym_call_expression] = ACTIONS(SHIFT(79)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(107)),
        [sym_string] = ACTIONS(SHIFT(79)),
        [sym_identifier] = ACTIONS(SHIFT(79)),
        [sym_number] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(55)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(56)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(111)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(107)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(112)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(113)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(114)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
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
    [114] = {
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
    [115] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(113)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [116] = {
        [sym__direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [117] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(25)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
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
    [119] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [120] = {
        [aux_sym_SLASH_LPAREN_BSLASH_LF_PIPE_DOT_RPAREN_STAR_SLASH] = ACTIONS(SHIFT(121)),
        [anon_sym_LF] = ACTIONS(SHIFT(122)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [121] = {
        [anon_sym_LF] = ACTIONS(SHIFT(123)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [122] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3)),
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
    [123] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4)),
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
    [124] = {
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
    [125] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(256)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(237)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(257)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(141)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(142)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(143)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(144)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(145)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
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
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(146)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(147)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
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
        [anon_sym_LBRACK] = ACTIONS(SHIFT(134)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(135)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(133)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(129)),
        [sym_identifier] = ACTIONS(SHIFT(130)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [sym_declarator] = ACTIONS(SHIFT(131)),
        [sym__direct_declarator] = ACTIONS(SHIFT(46)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(47)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(48)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
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
    [131] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(132)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
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
    [133] = {
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
        [anon_sym_LBRACK] = ACTIONS(SHIFT(134)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(135)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [sym_expression] = ACTIONS(SHIFT(140)),
        [sym_math_expression] = ACTIONS(SHIFT(79)),
        [sym_call_expression] = ACTIONS(SHIFT(79)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(132)),
        [sym_string] = ACTIONS(SHIFT(79)),
        [sym_identifier] = ACTIONS(SHIFT(79)),
        [sym_number] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(55)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(56)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(136)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(137)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(138)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(139)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
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
    [139] = {
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
    [140] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(138)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [sym__type_specifier] = ACTIONS(SHIFT(252)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
        [sym__init_declarator] = ACTIONS(SHIFT(248)),
        [sym_declarator] = ACTIONS(SHIFT(221)),
        [sym__direct_declarator] = ACTIONS(SHIFT(222)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(224)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(225)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(141)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(142)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(143)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(247)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
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
    [144] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
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
    [145] = {
        [sym_compound_statement] = ACTIONS(SHIFT(246)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(198)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(199)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(200)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(201)),
        [sym_math_expression] = ACTIONS(SHIFT(202)),
        [sym_call_expression] = ACTIONS(SHIFT(202)),
        [sym_statement] = ACTIONS(SHIFT(200)),
        [sym_expression_statement] = ACTIONS(SHIFT(203)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(204)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(204)),
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
        [anon_sym_RBRACE] = ACTIONS(SHIFT(205)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_string] = ACTIONS(SHIFT(202)),
        [sym_identifier] = ACTIONS(SHIFT(206)),
        [sym_number] = ACTIONS(SHIFT(202)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [sym_initializer] = ACTIONS(SHIFT(148)),
        [sym_expression] = ACTIONS(SHIFT(149)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(151)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(188)),
        [anon_sym_STAR] = ACTIONS(SHIFT(189)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(190)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [sym_initializer] = ACTIONS(SHIFT(152)),
        [sym_initializer_list] = ACTIONS(SHIFT(153)),
        [sym_designation] = ACTIONS(SHIFT(154)),
        [sym_expression] = ACTIONS(SHIFT(155)),
        [sym_math_expression] = ACTIONS(SHIFT(156)),
        [sym_call_expression] = ACTIONS(SHIFT(156)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(157)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(158)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(159)),
        [anon_sym_DOT] = ACTIONS(SHIFT(160)),
        [sym_string] = ACTIONS(SHIFT(156)),
        [sym_identifier] = ACTIONS(SHIFT(156)),
        [sym_number] = ACTIONS(SHIFT(156)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(185)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(186)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym_initializer] = ACTIONS(SHIFT(184)),
        [sym_expression] = ACTIONS(SHIFT(155)),
        [sym_math_expression] = ACTIONS(SHIFT(156)),
        [sym_call_expression] = ACTIONS(SHIFT(156)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(158)),
        [sym_string] = ACTIONS(SHIFT(156)),
        [sym_identifier] = ACTIONS(SHIFT(156)),
        [sym_number] = ACTIONS(SHIFT(156)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(174)),
        [anon_sym_STAR] = ACTIONS(SHIFT(175)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(176)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [sym_initializer] = ACTIONS(SHIFT(152)),
        [sym_initializer_list] = ACTIONS(SHIFT(166)),
        [sym_designation] = ACTIONS(SHIFT(154)),
        [sym_expression] = ACTIONS(SHIFT(155)),
        [sym_math_expression] = ACTIONS(SHIFT(156)),
        [sym_call_expression] = ACTIONS(SHIFT(156)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(157)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(158)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(159)),
        [anon_sym_DOT] = ACTIONS(SHIFT(160)),
        [sym_string] = ACTIONS(SHIFT(156)),
        [sym_identifier] = ACTIONS(SHIFT(156)),
        [sym_number] = ACTIONS(SHIFT(156)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [sym_expression] = ACTIONS(SHIFT(163)),
        [sym_math_expression] = ACTIONS(SHIFT(79)),
        [sym_call_expression] = ACTIONS(SHIFT(79)),
        [sym_string] = ACTIONS(SHIFT(79)),
        [sym_identifier] = ACTIONS(SHIFT(79)),
        [sym_number] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [sym_identifier] = ACTIONS(SHIFT(161)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(162)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(159)),
        [anon_sym_DOT] = ACTIONS(SHIFT(160)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(164)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(165)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(159)),
        [anon_sym_DOT] = ACTIONS(SHIFT(160)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(167)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(168)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [sym_initializer] = ACTIONS(SHIFT(169)),
        [sym_designation] = ACTIONS(SHIFT(170)),
        [sym_expression] = ACTIONS(SHIFT(155)),
        [sym_math_expression] = ACTIONS(SHIFT(156)),
        [sym_call_expression] = ACTIONS(SHIFT(156)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(157)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(158)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(171)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(159)),
        [anon_sym_DOT] = ACTIONS(SHIFT(160)),
        [sym_string] = ACTIONS(SHIFT(156)),
        [sym_identifier] = ACTIONS(SHIFT(156)),
        [sym_number] = ACTIONS(SHIFT(156)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [sym_initializer] = ACTIONS(SHIFT(172)),
        [sym_expression] = ACTIONS(SHIFT(155)),
        [sym_math_expression] = ACTIONS(SHIFT(156)),
        [sym_call_expression] = ACTIONS(SHIFT(156)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(158)),
        [sym_string] = ACTIONS(SHIFT(156)),
        [sym_identifier] = ACTIONS(SHIFT(156)),
        [sym_number] = ACTIONS(SHIFT(156)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [172] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
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
    [174] = {
        [sym_expression] = ACTIONS(SHIFT(179)),
        [sym_math_expression] = ACTIONS(SHIFT(86)),
        [sym_call_expression] = ACTIONS(SHIFT(86)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(180)),
        [sym_string] = ACTIONS(SHIFT(86)),
        [sym_identifier] = ACTIONS(SHIFT(86)),
        [sym_number] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [sym_expression] = ACTIONS(SHIFT(178)),
        [sym_math_expression] = ACTIONS(SHIFT(156)),
        [sym_call_expression] = ACTIONS(SHIFT(156)),
        [sym_string] = ACTIONS(SHIFT(156)),
        [sym_identifier] = ACTIONS(SHIFT(156)),
        [sym_number] = ACTIONS(SHIFT(156)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [sym_expression] = ACTIONS(SHIFT(177)),
        [sym_math_expression] = ACTIONS(SHIFT(156)),
        [sym_call_expression] = ACTIONS(SHIFT(156)),
        [sym_string] = ACTIONS(SHIFT(156)),
        [sym_identifier] = ACTIONS(SHIFT(156)),
        [sym_number] = ACTIONS(SHIFT(156)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(174)),
        [anon_sym_STAR] = ACTIONS(SHIFT(175)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(174)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(181)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(89)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(182)),
        [anon_sym_STAR] = ACTIONS(SHIFT(92)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [180] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(183)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [185] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [186] = {
        [sym_initializer] = ACTIONS(SHIFT(169)),
        [sym_designation] = ACTIONS(SHIFT(170)),
        [sym_expression] = ACTIONS(SHIFT(155)),
        [sym_math_expression] = ACTIONS(SHIFT(156)),
        [sym_call_expression] = ACTIONS(SHIFT(156)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(157)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(158)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(187)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(159)),
        [anon_sym_DOT] = ACTIONS(SHIFT(160)),
        [sym_string] = ACTIONS(SHIFT(156)),
        [sym_identifier] = ACTIONS(SHIFT(156)),
        [sym_number] = ACTIONS(SHIFT(156)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [188] = {
        [sym_expression] = ACTIONS(SHIFT(193)),
        [sym_math_expression] = ACTIONS(SHIFT(86)),
        [sym_call_expression] = ACTIONS(SHIFT(86)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(194)),
        [sym_string] = ACTIONS(SHIFT(86)),
        [sym_identifier] = ACTIONS(SHIFT(86)),
        [sym_number] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [sym_expression] = ACTIONS(SHIFT(192)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [sym_expression] = ACTIONS(SHIFT(191)),
        [sym_math_expression] = ACTIONS(SHIFT(150)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(188)),
        [anon_sym_STAR] = ACTIONS(SHIFT(189)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(188)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(195)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(89)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(196)),
        [anon_sym_STAR] = ACTIONS(SHIFT(92)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(197)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [sym__type_specifier] = ACTIONS(SHIFT(242)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [sym__init_declarator] = ACTIONS(SHIFT(220)),
        [sym_declarator] = ACTIONS(SHIFT(221)),
        [sym__direct_declarator] = ACTIONS(SHIFT(222)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(224)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(225)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(198)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(199)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(200)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_expression] = ACTIONS(SHIFT(201)),
        [sym_math_expression] = ACTIONS(SHIFT(202)),
        [sym_call_expression] = ACTIONS(SHIFT(202)),
        [sym_statement] = ACTIONS(SHIFT(200)),
        [sym_expression_statement] = ACTIONS(SHIFT(203)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(219)),
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
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_string] = ACTIONS(SHIFT(202)),
        [sym_identifier] = ACTIONS(SHIFT(206)),
        [sym_number] = ACTIONS(SHIFT(202)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(208)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(209)),
        [anon_sym_STAR] = ACTIONS(SHIFT(210)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
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
    [204] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(207)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_type_name] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
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
    [206] = {
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
    [207] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
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
    [208] = {
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
    [209] = {
        [sym_expression] = ACTIONS(SHIFT(214)),
        [sym_math_expression] = ACTIONS(SHIFT(86)),
        [sym_call_expression] = ACTIONS(SHIFT(86)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(215)),
        [sym_string] = ACTIONS(SHIFT(86)),
        [sym_identifier] = ACTIONS(SHIFT(86)),
        [sym_number] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [sym_expression] = ACTIONS(SHIFT(213)),
        [sym_math_expression] = ACTIONS(SHIFT(202)),
        [sym_call_expression] = ACTIONS(SHIFT(202)),
        [sym_string] = ACTIONS(SHIFT(202)),
        [sym_identifier] = ACTIONS(SHIFT(202)),
        [sym_number] = ACTIONS(SHIFT(202)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [sym_expression] = ACTIONS(SHIFT(212)),
        [sym_math_expression] = ACTIONS(SHIFT(202)),
        [sym_call_expression] = ACTIONS(SHIFT(202)),
        [sym_string] = ACTIONS(SHIFT(202)),
        [sym_identifier] = ACTIONS(SHIFT(202)),
        [sym_number] = ACTIONS(SHIFT(202)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(209)),
        [anon_sym_STAR] = ACTIONS(SHIFT(210)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [213] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(209)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(216)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(89)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(217)),
        [anon_sym_STAR] = ACTIONS(SHIFT(92)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(218)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [219] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(236)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(237)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(229)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(230)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
        [sym__direct_declarator] = ACTIONS(SHIFT(228)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(224)),
        [sym_identifier] = ACTIONS(SHIFT(225)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym_declarator] = ACTIONS(SHIFT(226)),
        [sym__direct_declarator] = ACTIONS(SHIFT(46)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(47)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(48)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [225] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(227)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [228] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(229)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(230)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [sym_expression] = ACTIONS(SHIFT(235)),
        [sym_math_expression] = ACTIONS(SHIFT(79)),
        [sym_call_expression] = ACTIONS(SHIFT(79)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(227)),
        [sym_string] = ACTIONS(SHIFT(79)),
        [sym_identifier] = ACTIONS(SHIFT(79)),
        [sym_number] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(55)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(56)),
        [sym_type_name] = ACTIONS(SHIFT(20)),
        [sym_struct_specifier] = ACTIONS(SHIFT(20)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(231)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(22)),
        [anon_sym_typedef] = ACTIONS(SHIFT(11)),
        [anon_sym_extern] = ACTIONS(SHIFT(11)),
        [anon_sym_static] = ACTIONS(SHIFT(11)),
        [anon_sym_auto] = ACTIONS(SHIFT(11)),
        [anon_sym_register] = ACTIONS(SHIFT(11)),
        [anon_sym_signed] = ACTIONS(SHIFT(12)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(12)),
        [anon_sym_long] = ACTIONS(SHIFT(12)),
        [anon_sym_short] = ACTIONS(SHIFT(12)),
        [anon_sym_struct] = ACTIONS(SHIFT(24)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(227)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [231] = {
        [aux_sym__direct_declarator_repeat1] = ACTIONS(SHIFT(232)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(233)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(234)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [233] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(233)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(241)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [237] = {
        [sym__init_declarator] = ACTIONS(SHIFT(239)),
        [sym_declarator] = ACTIONS(SHIFT(221)),
        [sym__direct_declarator] = ACTIONS(SHIFT(222)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(224)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(225)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [238] = {
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
    [239] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(240)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(237)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [240] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [241] = {
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
    [242] = {
        [sym__init_declarator] = ACTIONS(SHIFT(243)),
        [sym_declarator] = ACTIONS(SHIFT(221)),
        [sym__direct_declarator] = ACTIONS(SHIFT(222)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(224)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(225)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [243] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(244)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(237)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(241)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(245)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
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
    [246] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
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
    [247] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(249)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(237)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(250)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [250] = {
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
    [251] = {
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
    [252] = {
        [sym__init_declarator] = ACTIONS(SHIFT(253)),
        [sym_declarator] = ACTIONS(SHIFT(221)),
        [sym__direct_declarator] = ACTIONS(SHIFT(222)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(223)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(224)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(225)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(254)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(237)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(255)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
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
    [256] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(258)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
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
    [258] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
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
    [259] = {
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
    [260] = {
        [sym__init_declarator] = ACTIONS(SHIFT(261)),
        [sym_declarator] = ACTIONS(SHIFT(262)),
        [sym__direct_declarator] = ACTIONS(SHIFT(127)),
        [sym_pointer] = ACTIONS(SHIFT(40)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(128)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(129)),
        [anon_sym_STAR] = ACTIONS(SHIFT(43)),
        [sym_identifier] = ACTIONS(SHIFT(130)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [261] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(265)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(237)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(258)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [262] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(141)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(142)),
        [sym_type_name] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(143)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(246)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(263)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(9)),
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
        [anon_sym_struct] = ACTIONS(SHIFT(13)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(146)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(147)),
        [anon_sym_const] = ACTIONS(SHIFT(14)),
        [anon_sym_restrict] = ACTIONS(SHIFT(14)),
        [anon_sym_volatile] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
        [sym_compound_statement] = ACTIONS(SHIFT(264)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [264] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_function_definition, 5)),
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
    [265] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(266)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_name] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
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
    [267] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
