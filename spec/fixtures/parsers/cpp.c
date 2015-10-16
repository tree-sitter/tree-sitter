#include "tree_sitter/parser.h"

#define STATE_COUNT 293
#define SYMBOL_COUNT 83

enum {
    sym_translation_unit = ts_builtin_sym_start,
    sym__declaration,
    sym__block_declaration,
    sym_function_definition,
    sym_simple_declaration,
    sym_namespace_alias_definition,
    sym_scoped_identifier,
    sym_declarator,
    sym_abstract_declarator,
    sym_direct_declarator,
    sym_parameter_declaration,
    sym_direct_abstract_declarator,
    sym_cv_qualifier,
    sym_type_id,
    sym_pointer_operator,
    sym_function_body,
    sym_constructor_initializer,
    sym_member_initializer,
    sym_init_declarator,
    sym_decl_specifier,
    sym_storage_class_specifier,
    sym_type_specifier,
    sym_compound_statement,
    sym__statement,
    sym_expression_statement,
    sym_initializer,
    sym_initializer_clause,
    sym_function_specifier,
    sym__expression,
    sym_call_expression,
    sym_relational_expression,
    sym_template_call,
    aux_sym_translation_unit_repeat1,
    aux_sym_function_definition_repeat1,
    aux_sym_simple_declaration_repeat1,
    aux_sym_declarator_repeat1,
    aux_sym_direct_declarator_repeat1,
    aux_sym_pointer_operator_repeat1,
    aux_sym_constructor_initializer_repeat1,
    aux_sym_compound_statement_repeat1,
    aux_sym_call_expression_repeat1,
    anon_sym_EQ,
    anon_sym_default,
    anon_sym_delete,
    anon_sym_SEMI,
    anon_sym_COMMA,
    anon_sym_namespace,
    anon_sym_COLON_COLON,
    anon_sym_LPAREN,
    anon_sym_RPAREN,
    anon_sym_const,
    anon_sym_volatile,
    anon_sym_STAR,
    anon_sym_AMP,
    anon_sym_AMP_AMP,
    anon_sym_COLON,
    anon_sym_DOT_DOT_DOT,
    anon_sym_initializer_list,
    anon_sym_friend,
    anon_sym_typedef,
    anon_sym_constexpr,
    anon_sym_register,
    anon_sym_static,
    anon_sym_thread_local,
    anon_sym_extern,
    anon_sym_mutable,
    anon_sym_LBRACE,
    anon_sym_RBRACE,
    anon_sym_inline,
    anon_sym_virtual,
    anon_sym_explicit,
    anon_sym_GT,
    anon_sym_GT_EQ,
    anon_sym_EQ_EQ,
    anon_sym_BANG_EQ,
    anon_sym_LT_EQ,
    anon_sym_LT,
    sym_string,
    sym_identifier,
    sym_number,
    sym_comment,
};

static const char *ts_symbol_names[] = {
    [sym_translation_unit] = "translation_unit",
    [sym__declaration] = "_declaration",
    [sym__block_declaration] = "_block_declaration",
    [sym_function_definition] = "function_definition",
    [sym_simple_declaration] = "simple_declaration",
    [sym_namespace_alias_definition] = "namespace_alias_definition",
    [sym_scoped_identifier] = "scoped_identifier",
    [sym_declarator] = "declarator",
    [sym_abstract_declarator] = "abstract_declarator",
    [sym_direct_declarator] = "direct_declarator",
    [sym_parameter_declaration] = "parameter_declaration",
    [sym_direct_abstract_declarator] = "direct_abstract_declarator",
    [sym_cv_qualifier] = "cv_qualifier",
    [sym_type_id] = "type_id",
    [sym_pointer_operator] = "pointer_operator",
    [sym_function_body] = "function_body",
    [sym_constructor_initializer] = "constructor_initializer",
    [sym_member_initializer] = "member_initializer",
    [sym_init_declarator] = "init_declarator",
    [sym_decl_specifier] = "decl_specifier",
    [sym_storage_class_specifier] = "storage_class_specifier",
    [sym_type_specifier] = "type_specifier",
    [sym_compound_statement] = "compound_statement",
    [sym__statement] = "_statement",
    [sym_expression_statement] = "expression_statement",
    [sym_initializer] = "initializer",
    [sym_initializer_clause] = "initializer_clause",
    [sym_function_specifier] = "function_specifier",
    [sym__expression] = "_expression",
    [sym_call_expression] = "call_expression",
    [sym_relational_expression] = "relational_expression",
    [sym_template_call] = "template_call",
    [aux_sym_translation_unit_repeat1] = "translation_unit_repeat1",
    [aux_sym_function_definition_repeat1] = "function_definition_repeat1",
    [aux_sym_simple_declaration_repeat1] = "simple_declaration_repeat1",
    [aux_sym_declarator_repeat1] = "declarator_repeat1",
    [aux_sym_direct_declarator_repeat1] = "direct_declarator_repeat1",
    [aux_sym_pointer_operator_repeat1] = "pointer_operator_repeat1",
    [aux_sym_constructor_initializer_repeat1] = "constructor_initializer_repeat1",
    [aux_sym_compound_statement_repeat1] = "compound_statement_repeat1",
    [aux_sym_call_expression_repeat1] = "call_expression_repeat1",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
    [anon_sym_EQ] = "=",
    [anon_sym_default] = "default",
    [anon_sym_delete] = "delete",
    [anon_sym_SEMI] = ";",
    [anon_sym_COMMA] = ",",
    [anon_sym_namespace] = "namespace",
    [anon_sym_COLON_COLON] = "::",
    [anon_sym_LPAREN] = "(",
    [anon_sym_RPAREN] = ")",
    [anon_sym_const] = "const",
    [anon_sym_volatile] = "volatile",
    [anon_sym_STAR] = "*",
    [anon_sym_AMP] = "&",
    [anon_sym_AMP_AMP] = "&&",
    [anon_sym_COLON] = ":",
    [anon_sym_DOT_DOT_DOT] = "...",
    [anon_sym_initializer_list] = "initializer_list",
    [anon_sym_friend] = "friend",
    [anon_sym_typedef] = "typedef",
    [anon_sym_constexpr] = "constexpr",
    [anon_sym_register] = "register",
    [anon_sym_static] = "static",
    [anon_sym_thread_local] = "thread_local",
    [anon_sym_extern] = "extern",
    [anon_sym_mutable] = "mutable",
    [anon_sym_LBRACE] = "{",
    [anon_sym_RBRACE] = "}",
    [anon_sym_inline] = "inline",
    [anon_sym_virtual] = "virtual",
    [anon_sym_explicit] = "explicit",
    [anon_sym_GT] = ">",
    [anon_sym_GT_EQ] = ">=",
    [anon_sym_EQ_EQ] = "==",
    [anon_sym_BANG_EQ] = "!=",
    [anon_sym_LT_EQ] = "<=",
    [anon_sym_LT] = "<",
    [sym_string] = "string",
    [sym_identifier] = "identifier",
    [sym_number] = "number",
    [sym_comment] = "comment",
};

static const TSNodeType ts_node_types[SYMBOL_COUNT] = {
    [sym_translation_unit] = TSNodeTypeNamed,
    [sym__declaration] = TSNodeTypeHidden,
    [sym__block_declaration] = TSNodeTypeHidden,
    [sym_function_definition] = TSNodeTypeNamed,
    [sym_simple_declaration] = TSNodeTypeNamed,
    [sym_namespace_alias_definition] = TSNodeTypeNamed,
    [sym_scoped_identifier] = TSNodeTypeNamed,
    [sym_declarator] = TSNodeTypeNamed,
    [sym_abstract_declarator] = TSNodeTypeNamed,
    [sym_direct_declarator] = TSNodeTypeNamed,
    [sym_parameter_declaration] = TSNodeTypeNamed,
    [sym_direct_abstract_declarator] = TSNodeTypeNamed,
    [sym_cv_qualifier] = TSNodeTypeNamed,
    [sym_type_id] = TSNodeTypeNamed,
    [sym_pointer_operator] = TSNodeTypeNamed,
    [sym_function_body] = TSNodeTypeNamed,
    [sym_constructor_initializer] = TSNodeTypeNamed,
    [sym_member_initializer] = TSNodeTypeNamed,
    [sym_init_declarator] = TSNodeTypeNamed,
    [sym_decl_specifier] = TSNodeTypeNamed,
    [sym_storage_class_specifier] = TSNodeTypeNamed,
    [sym_type_specifier] = TSNodeTypeNamed,
    [sym_compound_statement] = TSNodeTypeNamed,
    [sym__statement] = TSNodeTypeHidden,
    [sym_expression_statement] = TSNodeTypeNamed,
    [sym_initializer] = TSNodeTypeNamed,
    [sym_initializer_clause] = TSNodeTypeNamed,
    [sym_function_specifier] = TSNodeTypeNamed,
    [sym__expression] = TSNodeTypeHidden,
    [sym_call_expression] = TSNodeTypeNamed,
    [sym_relational_expression] = TSNodeTypeNamed,
    [sym_template_call] = TSNodeTypeNamed,
    [aux_sym_translation_unit_repeat1] = TSNodeTypeHidden,
    [aux_sym_function_definition_repeat1] = TSNodeTypeHidden,
    [aux_sym_simple_declaration_repeat1] = TSNodeTypeHidden,
    [aux_sym_declarator_repeat1] = TSNodeTypeHidden,
    [aux_sym_direct_declarator_repeat1] = TSNodeTypeHidden,
    [aux_sym_pointer_operator_repeat1] = TSNodeTypeHidden,
    [aux_sym_constructor_initializer_repeat1] = TSNodeTypeHidden,
    [aux_sym_compound_statement_repeat1] = TSNodeTypeHidden,
    [aux_sym_call_expression_repeat1] = TSNodeTypeHidden,
    [ts_builtin_sym_error] = TSNodeTypeNamed,
    [ts_builtin_sym_end] = TSNodeTypeHidden,
    [anon_sym_EQ] = TSNodeTypeAnonymous,
    [anon_sym_default] = TSNodeTypeAnonymous,
    [anon_sym_delete] = TSNodeTypeAnonymous,
    [anon_sym_SEMI] = TSNodeTypeAnonymous,
    [anon_sym_COMMA] = TSNodeTypeAnonymous,
    [anon_sym_namespace] = TSNodeTypeAnonymous,
    [anon_sym_COLON_COLON] = TSNodeTypeAnonymous,
    [anon_sym_LPAREN] = TSNodeTypeAnonymous,
    [anon_sym_RPAREN] = TSNodeTypeAnonymous,
    [anon_sym_const] = TSNodeTypeAnonymous,
    [anon_sym_volatile] = TSNodeTypeAnonymous,
    [anon_sym_STAR] = TSNodeTypeAnonymous,
    [anon_sym_AMP] = TSNodeTypeAnonymous,
    [anon_sym_AMP_AMP] = TSNodeTypeAnonymous,
    [anon_sym_COLON] = TSNodeTypeAnonymous,
    [anon_sym_DOT_DOT_DOT] = TSNodeTypeAnonymous,
    [anon_sym_initializer_list] = TSNodeTypeAnonymous,
    [anon_sym_friend] = TSNodeTypeAnonymous,
    [anon_sym_typedef] = TSNodeTypeAnonymous,
    [anon_sym_constexpr] = TSNodeTypeAnonymous,
    [anon_sym_register] = TSNodeTypeAnonymous,
    [anon_sym_static] = TSNodeTypeAnonymous,
    [anon_sym_thread_local] = TSNodeTypeAnonymous,
    [anon_sym_extern] = TSNodeTypeAnonymous,
    [anon_sym_mutable] = TSNodeTypeAnonymous,
    [anon_sym_LBRACE] = TSNodeTypeAnonymous,
    [anon_sym_RBRACE] = TSNodeTypeAnonymous,
    [anon_sym_inline] = TSNodeTypeAnonymous,
    [anon_sym_virtual] = TSNodeTypeAnonymous,
    [anon_sym_explicit] = TSNodeTypeAnonymous,
    [anon_sym_GT] = TSNodeTypeAnonymous,
    [anon_sym_GT_EQ] = TSNodeTypeAnonymous,
    [anon_sym_EQ_EQ] = TSNodeTypeAnonymous,
    [anon_sym_BANG_EQ] = TSNodeTypeAnonymous,
    [anon_sym_LT_EQ] = TSNodeTypeAnonymous,
    [anon_sym_LT] = TSNodeTypeAnonymous,
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
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(6);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(33);
            if (lookahead == 'm')
                ADVANCE(39);
            if (lookahead == 'n')
                ADVANCE(46);
            if (lookahead == 'r')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(87);
            LEX_ERROR();
        case 2:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 3:
            if (lookahead == '/')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(4);
            ACCEPT_TOKEN(sym_comment);
        case 5:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(sym_identifier);
        case 6:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'o')
                ADVANCE(7);
            ACCEPT_TOKEN(sym_identifier);
        case 7:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(8);
            ACCEPT_TOKEN(sym_identifier);
        case 8:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 's')
                ADVANCE(9);
            ACCEPT_TOKEN(sym_identifier);
        case 9:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(10);
            ACCEPT_TOKEN(sym_identifier);
        case 10:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(11);
            ACCEPT_TOKEN(sym_identifier);
        case 11:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'w') ||
                (lookahead == 'y') ||
                (lookahead == 'z'))
                ADVANCE(5);
            if (lookahead == 'x')
                ADVANCE(12);
            ACCEPT_TOKEN(sym_identifier);
        case 12:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'p')
                ADVANCE(13);
            ACCEPT_TOKEN(sym_identifier);
        case 13:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'r')
                ADVANCE(14);
            ACCEPT_TOKEN(sym_identifier);
        case 14:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_constexpr);
        case 15:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'w') ||
                (lookahead == 'y') ||
                (lookahead == 'z'))
                ADVANCE(5);
            if (lookahead == 'x')
                ADVANCE(16);
            ACCEPT_TOKEN(sym_identifier);
        case 16:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'p')
                ADVANCE(17);
            if (lookahead == 't')
                ADVANCE(23);
            ACCEPT_TOKEN(sym_identifier);
        case 17:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(18);
            ACCEPT_TOKEN(sym_identifier);
        case 18:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(19);
            ACCEPT_TOKEN(sym_identifier);
        case 19:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(20);
            ACCEPT_TOKEN(sym_identifier);
        case 20:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(21);
            ACCEPT_TOKEN(sym_identifier);
        case 21:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(22);
            ACCEPT_TOKEN(sym_identifier);
        case 22:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_explicit);
        case 23:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(24);
            ACCEPT_TOKEN(sym_identifier);
        case 24:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'r')
                ADVANCE(25);
            ACCEPT_TOKEN(sym_identifier);
        case 25:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(26);
            ACCEPT_TOKEN(sym_identifier);
        case 26:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_extern);
        case 27:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'r')
                ADVANCE(28);
            ACCEPT_TOKEN(sym_identifier);
        case 28:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(29);
            ACCEPT_TOKEN(sym_identifier);
        case 29:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(30);
            ACCEPT_TOKEN(sym_identifier);
        case 30:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(31);
            ACCEPT_TOKEN(sym_identifier);
        case 31:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'd')
                ADVANCE(32);
            ACCEPT_TOKEN(sym_identifier);
        case 32:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_friend);
        case 33:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(34);
            ACCEPT_TOKEN(sym_identifier);
        case 34:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(35);
            ACCEPT_TOKEN(sym_identifier);
        case 35:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(36);
            ACCEPT_TOKEN(sym_identifier);
        case 36:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(37);
            ACCEPT_TOKEN(sym_identifier);
        case 37:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(38);
            ACCEPT_TOKEN(sym_identifier);
        case 38:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_inline);
        case 39:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'u')
                ADVANCE(40);
            ACCEPT_TOKEN(sym_identifier);
        case 40:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(41);
            ACCEPT_TOKEN(sym_identifier);
        case 41:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(42);
            ACCEPT_TOKEN(sym_identifier);
        case 42:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                ('c' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'b')
                ADVANCE(43);
            ACCEPT_TOKEN(sym_identifier);
        case 43:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(44);
            ACCEPT_TOKEN(sym_identifier);
        case 44:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(45);
            ACCEPT_TOKEN(sym_identifier);
        case 45:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_mutable);
        case 46:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(47);
            ACCEPT_TOKEN(sym_identifier);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'm')
                ADVANCE(48);
            ACCEPT_TOKEN(sym_identifier);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(49);
            ACCEPT_TOKEN(sym_identifier);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 's')
                ADVANCE(50);
            ACCEPT_TOKEN(sym_identifier);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'p')
                ADVANCE(51);
            ACCEPT_TOKEN(sym_identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(52);
            ACCEPT_TOKEN(sym_identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(53);
            ACCEPT_TOKEN(sym_identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(54);
            ACCEPT_TOKEN(sym_identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_namespace);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(56);
            ACCEPT_TOKEN(sym_identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'g')
                ADVANCE(57);
            ACCEPT_TOKEN(sym_identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(58);
            ACCEPT_TOKEN(sym_identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 's')
                ADVANCE(59);
            ACCEPT_TOKEN(sym_identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(60);
            ACCEPT_TOKEN(sym_identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(61);
            ACCEPT_TOKEN(sym_identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'r')
                ADVANCE(62);
            ACCEPT_TOKEN(sym_identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_register);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(64);
            ACCEPT_TOKEN(sym_identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(65);
            ACCEPT_TOKEN(sym_identifier);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(66);
            ACCEPT_TOKEN(sym_identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(67);
            ACCEPT_TOKEN(sym_identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(68);
            ACCEPT_TOKEN(sym_identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_static);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('i' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(5);
            if (lookahead == 'h')
                ADVANCE(70);
            if (lookahead == 'y')
                ADVANCE(81);
            ACCEPT_TOKEN(sym_identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'r')
                ADVANCE(71);
            ACCEPT_TOKEN(sym_identifier);
        case 71:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(72);
            ACCEPT_TOKEN(sym_identifier);
        case 72:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(73);
            ACCEPT_TOKEN(sym_identifier);
        case 73:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'd')
                ADVANCE(74);
            ACCEPT_TOKEN(sym_identifier);
        case 74:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == '_')
                ADVANCE(75);
            ACCEPT_TOKEN(sym_identifier);
        case 75:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(76);
            ACCEPT_TOKEN(sym_identifier);
        case 76:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'o')
                ADVANCE(77);
            ACCEPT_TOKEN(sym_identifier);
        case 77:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(78);
            ACCEPT_TOKEN(sym_identifier);
        case 78:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(79);
            ACCEPT_TOKEN(sym_identifier);
        case 79:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(80);
            ACCEPT_TOKEN(sym_identifier);
        case 80:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_thread_local);
        case 81:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'p')
                ADVANCE(82);
            ACCEPT_TOKEN(sym_identifier);
        case 82:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(83);
            ACCEPT_TOKEN(sym_identifier);
        case 83:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'd')
                ADVANCE(84);
            ACCEPT_TOKEN(sym_identifier);
        case 84:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(85);
            ACCEPT_TOKEN(sym_identifier);
        case 85:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'f')
                ADVANCE(86);
            ACCEPT_TOKEN(sym_identifier);
        case 86:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_typedef);
        case 87:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(88);
            ACCEPT_TOKEN(sym_identifier);
        case 88:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'r')
                ADVANCE(89);
            ACCEPT_TOKEN(sym_identifier);
        case 89:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(90);
            ACCEPT_TOKEN(sym_identifier);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'u')
                ADVANCE(91);
            ACCEPT_TOKEN(sym_identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(92);
            ACCEPT_TOKEN(sym_identifier);
        case 92:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(93);
            ACCEPT_TOKEN(sym_identifier);
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_virtual);
        case 94:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(94);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 95:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(95);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 96:
            if (lookahead == '&')
                ADVANCE(97);
            ACCEPT_TOKEN(anon_sym_AMP);
        case 97:
            ACCEPT_TOKEN(anon_sym_AMP_AMP);
        case 98:
            ACCEPT_TOKEN(anon_sym_LPAREN);
        case 99:
            ACCEPT_TOKEN(anon_sym_STAR);
        case 100:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(6);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(33);
            if (lookahead == 'm')
                ADVANCE(39);
            if (lookahead == 'r')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(87);
            LEX_ERROR();
        case 101:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 102:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(102);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(103);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 103:
            if (lookahead == ':')
                ADVANCE(104);
            LEX_ERROR();
        case 104:
            ACCEPT_TOKEN(anon_sym_COLON_COLON);
        case 105:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(105);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(106);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(anon_sym_EQ);
        case 107:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(103);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(103);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(6);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(33);
            if (lookahead == 'm')
                ADVANCE(39);
            if (lookahead == 'n')
                ADVANCE(46);
            if (lookahead == 'r')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(87);
            LEX_ERROR();
        case 109:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(106);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 110:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 111:
            ACCEPT_TOKEN(anon_sym_COLON);
        case 112:
            ACCEPT_TOKEN(anon_sym_SEMI);
        case 113:
            ACCEPT_TOKEN(anon_sym_LBRACE);
        case 114:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(114);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(106);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 115:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(112);
            LEX_ERROR();
        case 116:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 117:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(118);
            if (lookahead == 'v')
                ADVANCE(123);
            LEX_ERROR();
        case 118:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'o')
                ADVANCE(119);
            ACCEPT_TOKEN(sym_identifier);
        case 119:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(120);
            ACCEPT_TOKEN(sym_identifier);
        case 120:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 's')
                ADVANCE(121);
            ACCEPT_TOKEN(sym_identifier);
        case 121:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(122);
            ACCEPT_TOKEN(sym_identifier);
        case 122:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_const);
        case 123:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'o')
                ADVANCE(124);
            ACCEPT_TOKEN(sym_identifier);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(125);
            ACCEPT_TOKEN(sym_identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(126);
            ACCEPT_TOKEN(sym_identifier);
        case 126:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(127);
            ACCEPT_TOKEN(sym_identifier);
        case 127:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(128);
            ACCEPT_TOKEN(sym_identifier);
        case 128:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(129);
            ACCEPT_TOKEN(sym_identifier);
        case 129:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(130);
            ACCEPT_TOKEN(sym_identifier);
        case 130:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_volatile);
        case 131:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(131);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 132:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 134:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(6);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(33);
            if (lookahead == 'm')
                ADVANCE(39);
            if (lookahead == 'r')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(87);
            LEX_ERROR();
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 137:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(112);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(106);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(106);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 141:
            if (lookahead == '\"')
                ADVANCE(142);
            if (lookahead == '\\')
                ADVANCE(143);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(141);
            LEX_ERROR();
        case 142:
            ACCEPT_TOKEN(sym_string);
        case 143:
            if (lookahead == '\"')
                ADVANCE(144);
            if (lookahead == '\\')
                ADVANCE(143);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(141);
            LEX_ERROR();
        case 144:
            if (lookahead == '\"')
                ADVANCE(142);
            if (lookahead == '\\')
                ADVANCE(143);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(141);
            ACCEPT_TOKEN(sym_string);
        case 145:
            if (lookahead == '.')
                ADVANCE(146);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            ACCEPT_TOKEN(sym_number);
        case 146:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(147);
            LEX_ERROR();
        case 147:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(147);
            ACCEPT_TOKEN(sym_number);
        case 148:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 149:
            if (lookahead == '=')
                ADVANCE(150);
            LEX_ERROR();
        case 150:
            ACCEPT_TOKEN(anon_sym_BANG_EQ);
        case 151:
            if (lookahead == '=')
                ADVANCE(152);
            ACCEPT_TOKEN(anon_sym_LT);
        case 152:
            ACCEPT_TOKEN(anon_sym_LT_EQ);
        case 153:
            if (lookahead == '=')
                ADVANCE(154);
            LEX_ERROR();
        case 154:
            ACCEPT_TOKEN(anon_sym_EQ_EQ);
        case 155:
            if (lookahead == '=')
                ADVANCE(156);
            ACCEPT_TOKEN(anon_sym_GT);
        case 156:
            ACCEPT_TOKEN(anon_sym_GT_EQ);
        case 157:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(157);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(103);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 158:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(158);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 159:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '>')
                ADVANCE(160);
            LEX_ERROR();
        case 160:
            ACCEPT_TOKEN(anon_sym_GT);
        case 161:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(161);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '>')
                ADVANCE(160);
            LEX_ERROR();
        case 162:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(162);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 163:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(163);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(103);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 164:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(164);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 165:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(165);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 166:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(166);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(103);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 167:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(167);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 168:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(168);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(103);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 169:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(169);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 170:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(170);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 171:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(171);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 172:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(172);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 173:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(173);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'c')
                ADVANCE(174);
            if (lookahead == 'v')
                ADVANCE(179);
            LEX_ERROR();
        case 174:
            if (lookahead == 'o')
                ADVANCE(175);
            LEX_ERROR();
        case 175:
            if (lookahead == 'n')
                ADVANCE(176);
            LEX_ERROR();
        case 176:
            if (lookahead == 's')
                ADVANCE(177);
            LEX_ERROR();
        case 177:
            if (lookahead == 't')
                ADVANCE(178);
            LEX_ERROR();
        case 178:
            ACCEPT_TOKEN(anon_sym_const);
        case 179:
            if (lookahead == 'o')
                ADVANCE(180);
            LEX_ERROR();
        case 180:
            if (lookahead == 'l')
                ADVANCE(181);
            LEX_ERROR();
        case 181:
            if (lookahead == 'a')
                ADVANCE(182);
            LEX_ERROR();
        case 182:
            if (lookahead == 't')
                ADVANCE(183);
            LEX_ERROR();
        case 183:
            if (lookahead == 'i')
                ADVANCE(184);
            LEX_ERROR();
        case 184:
            if (lookahead == 'l')
                ADVANCE(185);
            LEX_ERROR();
        case 185:
            if (lookahead == 'e')
                ADVANCE(186);
            LEX_ERROR();
        case 186:
            ACCEPT_TOKEN(anon_sym_volatile);
        case 187:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(187);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 188:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(188);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'd')
                ADVANCE(189);
            LEX_ERROR();
        case 189:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(190);
            ACCEPT_TOKEN(sym_identifier);
        case 190:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'f')
                ADVANCE(191);
            if (lookahead == 'l')
                ADVANCE(196);
            ACCEPT_TOKEN(sym_identifier);
        case 191:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(192);
            ACCEPT_TOKEN(sym_identifier);
        case 192:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'u')
                ADVANCE(193);
            ACCEPT_TOKEN(sym_identifier);
        case 193:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(194);
            ACCEPT_TOKEN(sym_identifier);
        case 194:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(195);
            ACCEPT_TOKEN(sym_identifier);
        case 195:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_default);
        case 196:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(197);
            ACCEPT_TOKEN(sym_identifier);
        case 197:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(198);
            ACCEPT_TOKEN(sym_identifier);
        case 198:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(199);
            ACCEPT_TOKEN(sym_identifier);
        case 199:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_delete);
        case 200:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(200);
            if (lookahead == '.')
                ADVANCE(201);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 201:
            if (lookahead == '.')
                ADVANCE(202);
            LEX_ERROR();
        case 202:
            if (lookahead == '.')
                ADVANCE(203);
            LEX_ERROR();
        case 203:
            ACCEPT_TOKEN(anon_sym_DOT_DOT_DOT);
        case 204:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(204);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (lookahead == ';')
                ADVANCE(112);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(6);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(33);
            if (lookahead == 'm')
                ADVANCE(39);
            if (lookahead == 'n')
                ADVANCE(46);
            if (lookahead == 'r')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(87);
            if (lookahead == '{')
                ADVANCE(113);
            if (lookahead == '}')
                ADVANCE(205);
            LEX_ERROR();
        case 205:
            ACCEPT_TOKEN(anon_sym_RBRACE);
        case 206:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(206);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 207:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(207);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 208:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(208);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(205);
            LEX_ERROR();
        case 209:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(209);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(103);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 210:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(210);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 211:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(211);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (lookahead == ':')
                ADVANCE(103);
            if (lookahead == ';')
                ADVANCE(112);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(6);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(33);
            if (lookahead == 'm')
                ADVANCE(39);
            if (lookahead == 'n')
                ADVANCE(46);
            if (lookahead == 'r')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(87);
            if (lookahead == '{')
                ADVANCE(113);
            if (lookahead == '}')
                ADVANCE(205);
            LEX_ERROR();
        case 212:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(212);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(103);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(155);
            LEX_ERROR();
        case 213:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(213);
            if (lookahead == '.')
                ADVANCE(201);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 214:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(214);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'i')
                ADVANCE(215);
            LEX_ERROR();
        case 215:
            if (lookahead == 'n')
                ADVANCE(216);
            LEX_ERROR();
        case 216:
            if (lookahead == 'i')
                ADVANCE(217);
            LEX_ERROR();
        case 217:
            if (lookahead == 't')
                ADVANCE(218);
            LEX_ERROR();
        case 218:
            if (lookahead == 'i')
                ADVANCE(219);
            LEX_ERROR();
        case 219:
            if (lookahead == 'a')
                ADVANCE(220);
            LEX_ERROR();
        case 220:
            if (lookahead == 'l')
                ADVANCE(221);
            LEX_ERROR();
        case 221:
            if (lookahead == 'i')
                ADVANCE(222);
            LEX_ERROR();
        case 222:
            if (lookahead == 'z')
                ADVANCE(223);
            LEX_ERROR();
        case 223:
            if (lookahead == 'e')
                ADVANCE(224);
            LEX_ERROR();
        case 224:
            if (lookahead == 'r')
                ADVANCE(225);
            LEX_ERROR();
        case 225:
            if (lookahead == '_')
                ADVANCE(226);
            LEX_ERROR();
        case 226:
            if (lookahead == 'l')
                ADVANCE(227);
            LEX_ERROR();
        case 227:
            if (lookahead == 'i')
                ADVANCE(228);
            LEX_ERROR();
        case 228:
            if (lookahead == 's')
                ADVANCE(229);
            LEX_ERROR();
        case 229:
            if (lookahead == 't')
                ADVANCE(230);
            LEX_ERROR();
        case 230:
            ACCEPT_TOKEN(anon_sym_initializer_list);
        case 231:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(231);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '.')
                ADVANCE(201);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (lookahead == ':')
                ADVANCE(232);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(233);
            if (lookahead == '>')
                ADVANCE(155);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(234);
            if (lookahead == 'd')
                ADVANCE(189);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(239);
            if (lookahead == 'm')
                ADVANCE(39);
            if (lookahead == 'n')
                ADVANCE(46);
            if (lookahead == 'r')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(255);
            if (lookahead == '{')
                ADVANCE(113);
            if (lookahead == '}')
                ADVANCE(205);
            LEX_ERROR();
        case 232:
            if (lookahead == ':')
                ADVANCE(104);
            ACCEPT_TOKEN(anon_sym_COLON);
        case 233:
            if (lookahead == '=')
                ADVANCE(154);
            ACCEPT_TOKEN(anon_sym_EQ);
        case 234:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'o')
                ADVANCE(235);
            ACCEPT_TOKEN(sym_identifier);
        case 235:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(236);
            ACCEPT_TOKEN(sym_identifier);
        case 236:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 's')
                ADVANCE(237);
            ACCEPT_TOKEN(sym_identifier);
        case 237:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(238);
            ACCEPT_TOKEN(sym_identifier);
        case 238:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(11);
            ACCEPT_TOKEN(anon_sym_const);
        case 239:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(240);
            ACCEPT_TOKEN(sym_identifier);
        case 240:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                (lookahead == 'j') ||
                (lookahead == 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(241);
            if (lookahead == 'l')
                ADVANCE(35);
            ACCEPT_TOKEN(sym_identifier);
        case 241:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(242);
            ACCEPT_TOKEN(sym_identifier);
        case 242:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(243);
            ACCEPT_TOKEN(sym_identifier);
        case 243:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(244);
            ACCEPT_TOKEN(sym_identifier);
        case 244:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(245);
            ACCEPT_TOKEN(sym_identifier);
        case 245:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(246);
            ACCEPT_TOKEN(sym_identifier);
        case 246:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'y'))
                ADVANCE(5);
            if (lookahead == 'z')
                ADVANCE(247);
            ACCEPT_TOKEN(sym_identifier);
        case 247:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(248);
            ACCEPT_TOKEN(sym_identifier);
        case 248:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'r')
                ADVANCE(249);
            ACCEPT_TOKEN(sym_identifier);
        case 249:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == '_')
                ADVANCE(250);
            ACCEPT_TOKEN(sym_identifier);
        case 250:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(251);
            ACCEPT_TOKEN(sym_identifier);
        case 251:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(252);
            ACCEPT_TOKEN(sym_identifier);
        case 252:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 's')
                ADVANCE(253);
            ACCEPT_TOKEN(sym_identifier);
        case 253:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(254);
            ACCEPT_TOKEN(sym_identifier);
        case 254:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_initializer_list);
        case 255:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(88);
            if (lookahead == 'o')
                ADVANCE(124);
            ACCEPT_TOKEN(sym_identifier);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(231);
            if (lookahead == '!')
                ADVANCE(149);
            if (lookahead == '\"')
                ADVANCE(141);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(132);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == ',')
                ADVANCE(110);
            if (lookahead == '.')
                ADVANCE(201);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(145);
            if (lookahead == ':')
                ADVANCE(232);
            if (lookahead == ';')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(151);
            if (lookahead == '=')
                ADVANCE(233);
            if (lookahead == '>')
                ADVANCE(155);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'c')
                ADVANCE(234);
            if (lookahead == 'd')
                ADVANCE(189);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(239);
            if (lookahead == 'm')
                ADVANCE(39);
            if (lookahead == 'n')
                ADVANCE(46);
            if (lookahead == 'r')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(69);
            if (lookahead == 'v')
                ADVANCE(255);
            if (lookahead == '{')
                ADVANCE(113);
            if (lookahead == '}')
                ADVANCE(205);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 94,
    [2] = 1,
    [3] = 1,
    [4] = 1,
    [5] = 95,
    [6] = 100,
    [7] = 100,
    [8] = 95,
    [9] = 94,
    [10] = 101,
    [11] = 101,
    [12] = 100,
    [13] = 100,
    [14] = 102,
    [15] = 101,
    [16] = 95,
    [17] = 102,
    [18] = 105,
    [19] = 101,
    [20] = 1,
    [21] = 107,
    [22] = 101,
    [23] = 1,
    [24] = 108,
    [25] = 95,
    [26] = 109,
    [27] = 114,
    [28] = 95,
    [29] = 115,
    [30] = 116,
    [31] = 95,
    [32] = 117,
    [33] = 95,
    [34] = 114,
    [35] = 117,
    [36] = 95,
    [37] = 117,
    [38] = 95,
    [39] = 131,
    [40] = 133,
    [41] = 116,
    [42] = 95,
    [43] = 133,
    [44] = 131,
    [45] = 133,
    [46] = 133,
    [47] = 134,
    [48] = 95,
    [49] = 135,
    [50] = 95,
    [51] = 101,
    [52] = 102,
    [53] = 101,
    [54] = 95,
    [55] = 102,
    [56] = 95,
    [57] = 135,
    [58] = 136,
    [59] = 135,
    [60] = 95,
    [61] = 116,
    [62] = 95,
    [63] = 117,
    [64] = 95,
    [65] = 136,
    [66] = 117,
    [67] = 95,
    [68] = 117,
    [69] = 95,
    [70] = 131,
    [71] = 131,
    [72] = 131,
    [73] = 116,
    [74] = 95,
    [75] = 131,
    [76] = 131,
    [77] = 131,
    [78] = 135,
    [79] = 136,
    [80] = 136,
    [81] = 135,
    [82] = 134,
    [83] = 135,
    [84] = 131,
    [85] = 100,
    [86] = 136,
    [87] = 135,
    [88] = 131,
    [89] = 136,
    [90] = 116,
    [91] = 135,
    [92] = 131,
    [93] = 133,
    [94] = 133,
    [95] = 114,
    [96] = 114,
    [97] = 134,
    [98] = 135,
    [99] = 131,
    [100] = 114,
    [101] = 114,
    [102] = 137,
    [103] = 1,
    [104] = 95,
    [105] = 138,
    [106] = 139,
    [107] = 115,
    [108] = 116,
    [109] = 95,
    [110] = 139,
    [111] = 131,
    [112] = 139,
    [113] = 139,
    [114] = 134,
    [115] = 135,
    [116] = 131,
    [117] = 139,
    [118] = 139,
    [119] = 137,
    [120] = 115,
    [121] = 140,
    [122] = 148,
    [123] = 115,
    [124] = 148,
    [125] = 148,
    [126] = 157,
    [127] = 101,
    [128] = 140,
    [129] = 158,
    [130] = 159,
    [131] = 161,
    [132] = 162,
    [133] = 162,
    [134] = 163,
    [135] = 101,
    [136] = 140,
    [137] = 159,
    [138] = 162,
    [139] = 164,
    [140] = 165,
    [141] = 140,
    [142] = 162,
    [143] = 162,
    [144] = 166,
    [145] = 101,
    [146] = 162,
    [147] = 166,
    [148] = 167,
    [149] = 167,
    [150] = 167,
    [151] = 162,
    [152] = 168,
    [153] = 101,
    [154] = 140,
    [155] = 159,
    [156] = 162,
    [157] = 169,
    [158] = 167,
    [159] = 167,
    [160] = 168,
    [161] = 131,
    [162] = 140,
    [163] = 164,
    [164] = 162,
    [165] = 140,
    [166] = 167,
    [167] = 167,
    [168] = 167,
    [169] = 131,
    [170] = 167,
    [171] = 167,
    [172] = 167,
    [173] = 131,
    [174] = 162,
    [175] = 162,
    [176] = 158,
    [177] = 163,
    [178] = 170,
    [179] = 159,
    [180] = 159,
    [181] = 171,
    [182] = 172,
    [183] = 171,
    [184] = 173,
    [185] = 171,
    [186] = 173,
    [187] = 171,
    [188] = 173,
    [189] = 171,
    [190] = 131,
    [191] = 172,
    [192] = 171,
    [193] = 159,
    [194] = 159,
    [195] = 172,
    [196] = 148,
    [197] = 148,
    [198] = 157,
    [199] = 164,
    [200] = 140,
    [201] = 148,
    [202] = 167,
    [203] = 148,
    [204] = 131,
    [205] = 148,
    [206] = 148,
    [207] = 1,
    [208] = 116,
    [209] = 1,
    [210] = 187,
    [211] = 1,
    [212] = 188,
    [213] = 200,
    [214] = 204,
    [215] = 204,
    [216] = 204,
    [217] = 206,
    [218] = 95,
    [219] = 204,
    [220] = 207,
    [221] = 207,
    [222] = 101,
    [223] = 208,
    [224] = 204,
    [225] = 101,
    [226] = 204,
    [227] = 1,
    [228] = 209,
    [229] = 101,
    [230] = 140,
    [231] = 159,
    [232] = 162,
    [233] = 210,
    [234] = 207,
    [235] = 206,
    [236] = 209,
    [237] = 208,
    [238] = 204,
    [239] = 204,
    [240] = 105,
    [241] = 101,
    [242] = 204,
    [243] = 107,
    [244] = 101,
    [245] = 204,
    [246] = 211,
    [247] = 1,
    [248] = 95,
    [249] = 115,
    [250] = 137,
    [251] = 204,
    [252] = 204,
    [253] = 204,
    [254] = 164,
    [255] = 140,
    [256] = 207,
    [257] = 207,
    [258] = 212,
    [259] = 101,
    [260] = 207,
    [261] = 212,
    [262] = 167,
    [263] = 207,
    [264] = 131,
    [265] = 207,
    [266] = 207,
    [267] = 208,
    [268] = 115,
    [269] = 137,
    [270] = 204,
    [271] = 200,
    [272] = 213,
    [273] = 187,
    [274] = 172,
    [275] = 214,
    [276] = 131,
    [277] = 200,
    [278] = 187,
    [279] = 213,
    [280] = 137,
    [281] = 1,
    [282] = 1,
    [283] = 109,
    [284] = 115,
    [285] = 137,
    [286] = 1,
    [287] = 1,
    [288] = 188,
    [289] = 137,
    [290] = 1,
    [291] = 101,
    [292] = 94,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction *ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_translation_unit] = ACTIONS(SHIFT(1)),
        [sym__declaration] = ACTIONS(SHIFT(2)),
        [sym__block_declaration] = ACTIONS(SHIFT(3)),
        [sym_function_definition] = ACTIONS(SHIFT(3)),
        [sym_simple_declaration] = ACTIONS(SHIFT(4)),
        [sym_namespace_alias_definition] = ACTIONS(SHIFT(4)),
        [sym_scoped_identifier] = ACTIONS(SHIFT(5)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(8)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(10)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_translation_unit, 0)),
        [anon_sym_namespace] = ACTIONS(SHIFT(11)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(14)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [1] = {
        [ts_builtin_sym_end] = ACTIONS(ACCEPT_INPUT()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [2] = {
        [sym__declaration] = ACTIONS(SHIFT(2)),
        [sym__block_declaration] = ACTIONS(SHIFT(3)),
        [sym_function_definition] = ACTIONS(SHIFT(3)),
        [sym_simple_declaration] = ACTIONS(SHIFT(4)),
        [sym_namespace_alias_definition] = ACTIONS(SHIFT(4)),
        [sym_scoped_identifier] = ACTIONS(SHIFT(5)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(8)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(292)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(10)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 1)),
        [anon_sym_namespace] = ACTIONS(SHIFT(11)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(14)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [3] = {
        [sym__declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_function_definition] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym__declaration, 1)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym__declaration, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__declaration, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [4] = {
        [sym__declaration] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_function_definition] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [5] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(291)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [7] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
        [sym_declarator] = ACTIONS(SHIFT(283)),
        [sym_direct_declarator] = ACTIONS(SHIFT(27)),
        [sym_pointer_operator] = ACTIONS(SHIFT(28)),
        [sym_init_declarator] = ACTIONS(SHIFT(284)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(30)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(31)),
        [anon_sym_STAR] = ACTIONS(SHIFT(32)),
        [anon_sym_AMP] = ACTIONS(SHIFT(33)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(SHIFT(34)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_translation_unit, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(5)),
        [sym_type_specifier] = ACTIONS(SHIFT(25)),
        [sym_identifier] = ACTIONS(SHIFT(14)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [sym_identifier] = ACTIONS(SHIFT(18)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(15)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [15] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(16)),
        [sym_identifier] = ACTIONS(SHIFT(17)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(15)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(19)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(20)),
        [sym_identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(23)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(22)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [sym_declarator] = ACTIONS(SHIFT(26)),
        [sym_direct_declarator] = ACTIONS(SHIFT(27)),
        [sym_pointer_operator] = ACTIONS(SHIFT(28)),
        [sym_init_declarator] = ACTIONS(SHIFT(29)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(30)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(31)),
        [anon_sym_STAR] = ACTIONS(SHIFT(32)),
        [anon_sym_AMP] = ACTIONS(SHIFT(33)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(SHIFT(34)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [sym_function_body] = ACTIONS(SHIFT(209)),
        [sym_constructor_initializer] = ACTIONS(SHIFT(210)),
        [sym_compound_statement] = ACTIONS(SHIFT(211)),
        [sym_initializer] = ACTIONS(SHIFT(120)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(212)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COLON] = ACTIONS(SHIFT(213)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(214)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [sym_function_body] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_constructor_initializer] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_initializer] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_COLON] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer_operator] = ACTIONS(SHIFT(28)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(208)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(32)),
        [anon_sym_AMP] = ACTIONS(SHIFT(33)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(102)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(103)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(104)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(96)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(31)),
        [sym_identifier] = ACTIONS(SHIFT(34)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [sym_declarator] = ACTIONS(SHIFT(39)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_pointer_operator] = ACTIONS(SHIFT(28)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(42)),
        [anon_sym_STAR] = ACTIONS(SHIFT(32)),
        [anon_sym_AMP] = ACTIONS(SHIFT(33)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(35)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(36)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(37)),
        [anon_sym_volatile] = ACTIONS(SHIFT(37)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [33] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [34] = {
        [sym_function_body] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_constructor_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_COLON] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [35] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(35)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(38)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(37)),
        [anon_sym_volatile] = ACTIONS(SHIFT(37)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [36] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [37] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_cv_qualifier] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [38] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [39] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(95)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [40] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(47)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [41] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(46)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(42)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [42] = {
        [sym_declarator] = ACTIONS(SHIFT(44)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_pointer_operator] = ACTIONS(SHIFT(28)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(42)),
        [anon_sym_STAR] = ACTIONS(SHIFT(32)),
        [anon_sym_AMP] = ACTIONS(SHIFT(33)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [43] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [44] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(45)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [45] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [46] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(47)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [47] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(48)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(49)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(51)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(45)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(52)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [48] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [49] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(92)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(85)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [50] = {
        [sym_declarator] = ACTIONS(SHIFT(91)),
        [sym_abstract_declarator] = ACTIONS(SHIFT(91)),
        [sym_direct_declarator] = ACTIONS(SHIFT(58)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(59)),
        [sym_pointer_operator] = ACTIONS(SHIFT(60)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(61)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(62)),
        [anon_sym_STAR] = ACTIONS(SHIFT(63)),
        [anon_sym_AMP] = ACTIONS(SHIFT(64)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(64)),
        [sym_identifier] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [51] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(48)),
        [sym_type_specifier] = ACTIONS(SHIFT(56)),
        [sym_identifier] = ACTIONS(SHIFT(52)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [52] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(53)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [53] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(54)),
        [sym_identifier] = ACTIONS(SHIFT(55)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [54] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [55] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(53)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [56] = {
        [sym_declarator] = ACTIONS(SHIFT(57)),
        [sym_abstract_declarator] = ACTIONS(SHIFT(57)),
        [sym_direct_declarator] = ACTIONS(SHIFT(58)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(59)),
        [sym_pointer_operator] = ACTIONS(SHIFT(60)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(61)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(62)),
        [anon_sym_STAR] = ACTIONS(SHIFT(63)),
        [anon_sym_AMP] = ACTIONS(SHIFT(64)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(64)),
        [sym_identifier] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [57] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [58] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(82)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [59] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [60] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer_operator] = ACTIONS(SHIFT(60)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(90)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(63)),
        [anon_sym_AMP] = ACTIONS(SHIFT(64)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(64)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [61] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(80)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(62)),
        [sym_identifier] = ACTIONS(SHIFT(65)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [62] = {
        [sym_declarator] = ACTIONS(SHIFT(70)),
        [sym_abstract_declarator] = ACTIONS(SHIFT(71)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(72)),
        [sym_pointer_operator] = ACTIONS(SHIFT(60)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(73)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_STAR] = ACTIONS(SHIFT(63)),
        [anon_sym_AMP] = ACTIONS(SHIFT(64)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(64)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [63] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(66)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(67)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(68)),
        [anon_sym_volatile] = ACTIONS(SHIFT(68)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [64] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [65] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [66] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(66)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(68)),
        [anon_sym_volatile] = ACTIONS(SHIFT(68)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [67] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [68] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_cv_qualifier] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [69] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [70] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [71] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [72] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(46)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(77)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [sym_declarator] = ACTIONS(SHIFT(44)),
        [sym_abstract_declarator] = ACTIONS(SHIFT(75)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(72)),
        [sym_pointer_operator] = ACTIONS(SHIFT(60)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(73)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_STAR] = ACTIONS(SHIFT(63)),
        [anon_sym_AMP] = ACTIONS(SHIFT(64)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(64)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [75] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(76)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [80] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(82)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [82] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(48)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(83)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(51)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(79)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(52)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(84)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(85)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(86)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(48)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(87)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(51)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(52)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(88)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(85)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_direct_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_direct_declarator_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(94)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [sym_function_body] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_constructor_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_COLON] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [sym_function_body] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_constructor_initializer] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_initializer] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_COLON] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(48)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(98)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(51)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(52)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(99)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(85)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(100)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [99] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [sym_function_body] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_constructor_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_COLON] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [sym_function_body] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_constructor_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_COLON] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(207)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [103] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [sym_declarator] = ACTIONS(SHIFT(105)),
        [sym_direct_declarator] = ACTIONS(SHIFT(106)),
        [sym_pointer_operator] = ACTIONS(SHIFT(28)),
        [sym_init_declarator] = ACTIONS(SHIFT(107)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(109)),
        [anon_sym_STAR] = ACTIONS(SHIFT(32)),
        [anon_sym_AMP] = ACTIONS(SHIFT(33)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(SHIFT(110)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
        [sym_initializer] = ACTIONS(SHIFT(120)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(121)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [106] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(114)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [107] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(119)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_simple_declaration_repeat1, 2)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(104)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [108] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(113)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(109)),
        [sym_identifier] = ACTIONS(SHIFT(110)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [sym_declarator] = ACTIONS(SHIFT(111)),
        [sym_direct_declarator] = ACTIONS(SHIFT(40)),
        [sym_pointer_operator] = ACTIONS(SHIFT(28)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(41)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(42)),
        [anon_sym_STAR] = ACTIONS(SHIFT(32)),
        [anon_sym_AMP] = ACTIONS(SHIFT(33)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(112)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(114)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(48)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(115)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(50)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(51)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(112)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(SHIFT(52)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(116)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(85)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(117)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [116] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(118)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [117] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [119] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_simple_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [120] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [121] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(122)),
        [sym_initializer_clause] = ACTIONS(SHIFT(123)),
        [sym__expression] = ACTIONS(SHIFT(124)),
        [sym_call_expression] = ACTIONS(SHIFT(125)),
        [sym_relational_expression] = ACTIONS(SHIFT(125)),
        [sym_template_call] = ACTIONS(SHIFT(125)),
        [sym_string] = ACTIONS(SHIFT(125)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [122] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(128)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [123] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [124] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer_clause, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer_clause, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_clause, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199)),
        [anon_sym_GT] = ACTIONS(SHIFT(200)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(200)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(200)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(200)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(200)),
        [anon_sym_LT] = ACTIONS(SHIFT(200)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [125] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(127)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(128)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(197)),
        [sym_identifier] = ACTIONS(SHIFT(198)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(129)),
        [sym_type_id] = ACTIONS(SHIFT(130)),
        [sym_type_specifier] = ACTIONS(SHIFT(131)),
        [sym__expression] = ACTIONS(SHIFT(132)),
        [sym_call_expression] = ACTIONS(SHIFT(133)),
        [sym_relational_expression] = ACTIONS(SHIFT(133)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [sym_string] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(134)),
        [sym_number] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(136)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [anon_sym_GT] = ACTIONS(SHIFT(196)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [131] = {
        [sym_abstract_declarator] = ACTIONS(SHIFT(179)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(180)),
        [sym_pointer_operator] = ACTIONS(SHIFT(181)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(182)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(183)),
        [anon_sym_STAR] = ACTIONS(SHIFT(184)),
        [anon_sym_AMP] = ACTIONS(SHIFT(185)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(185)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_type_id, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(139)),
        [anon_sym_GT] = ACTIONS(SHIFT(178)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_LT] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [133] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(135)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(136)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(176)),
        [sym_identifier] = ACTIONS(SHIFT(177)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(129)),
        [sym_type_id] = ACTIONS(SHIFT(137)),
        [sym_type_specifier] = ACTIONS(SHIFT(131)),
        [sym__expression] = ACTIONS(SHIFT(138)),
        [sym_call_expression] = ACTIONS(SHIFT(133)),
        [sym_relational_expression] = ACTIONS(SHIFT(133)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [sym_string] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(134)),
        [sym_number] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [anon_sym_GT] = ACTIONS(SHIFT(175)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(139)),
        [anon_sym_GT] = ACTIONS(SHIFT(140)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_LT] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [139] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(148)),
        [sym__expression] = ACTIONS(SHIFT(149)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_relational_expression] = ACTIONS(SHIFT(150)),
        [sym_template_call] = ACTIONS(SHIFT(150)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(151)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(152)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [140] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(142)),
        [sym__expression] = ACTIONS(SHIFT(143)),
        [sym_call_expression] = ACTIONS(SHIFT(133)),
        [sym_relational_expression] = ACTIONS(SHIFT(133)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(144)),
        [sym_number] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(142)),
        [sym__expression] = ACTIONS(SHIFT(143)),
        [sym_call_expression] = ACTIONS(SHIFT(133)),
        [sym_relational_expression] = ACTIONS(SHIFT(133)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [sym_string] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(144)),
        [sym_number] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(136)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [144] = {
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(145)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(136)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [145] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(145)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(154)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(161)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(162)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(163)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(164)),
        [anon_sym_GT] = ACTIONS(SHIFT(165)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(153)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(154)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(159)),
        [sym_identifier] = ACTIONS(SHIFT(160)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(129)),
        [sym_type_id] = ACTIONS(SHIFT(155)),
        [sym_type_specifier] = ACTIONS(SHIFT(131)),
        [sym__expression] = ACTIONS(SHIFT(156)),
        [sym_call_expression] = ACTIONS(SHIFT(133)),
        [sym_relational_expression] = ACTIONS(SHIFT(133)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [sym_string] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(134)),
        [sym_number] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [anon_sym_GT] = ACTIONS(SHIFT(158)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(139)),
        [anon_sym_GT] = ACTIONS(SHIFT(157)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_LT] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(142)),
        [sym__expression] = ACTIONS(SHIFT(143)),
        [sym_call_expression] = ACTIONS(SHIFT(133)),
        [sym_relational_expression] = ACTIONS(SHIFT(133)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(144)),
        [sym_number] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(153)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(174)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(148)),
        [sym__expression] = ACTIONS(SHIFT(172)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_relational_expression] = ACTIONS(SHIFT(150)),
        [sym_template_call] = ACTIONS(SHIFT(150)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(152)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(148)),
        [sym__expression] = ACTIONS(SHIFT(167)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_relational_expression] = ACTIONS(SHIFT(150)),
        [sym_template_call] = ACTIONS(SHIFT(150)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(168)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(152)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(148)),
        [sym__expression] = ACTIONS(SHIFT(166)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_relational_expression] = ACTIONS(SHIFT(150)),
        [sym_template_call] = ACTIONS(SHIFT(150)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(152)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(169)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(162)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(163)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(170)),
        [anon_sym_GT] = ACTIONS(SHIFT(165)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(171)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [172] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(173)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(162)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(163)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [anon_sym_GT] = ACTIONS(SHIFT(165)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(135)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(142)),
        [sym__expression] = ACTIONS(SHIFT(143)),
        [sym_call_expression] = ACTIONS(SHIFT(133)),
        [sym_relational_expression] = ACTIONS(SHIFT(133)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(144)),
        [sym_number] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
        [anon_sym_GT] = ACTIONS(REDUCE(sym_type_id, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [180] = {
        [anon_sym_GT] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer_operator] = ACTIONS(SHIFT(181)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(195)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(184)),
        [anon_sym_AMP] = ACTIONS(SHIFT(185)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(185)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(194)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(183)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [sym_abstract_declarator] = ACTIONS(SHIFT(190)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(72)),
        [sym_pointer_operator] = ACTIONS(SHIFT(181)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(191)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(192)),
        [anon_sym_STAR] = ACTIONS(SHIFT(184)),
        [anon_sym_AMP] = ACTIONS(SHIFT(185)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(185)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(186)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(187)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(188)),
        [anon_sym_volatile] = ACTIONS(SHIFT(188)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [185] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [186] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(186)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(189)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(188)),
        [anon_sym_volatile] = ACTIONS(SHIFT(188)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [188] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_cv_qualifier] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_cv_qualifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(193)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(77)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(192)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [sym_abstract_declarator] = ACTIONS(SHIFT(75)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(72)),
        [sym_pointer_operator] = ACTIONS(SHIFT(181)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(191)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(192)),
        [anon_sym_STAR] = ACTIONS(SHIFT(184)),
        [anon_sym_AMP] = ACTIONS(SHIFT(185)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(185)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [anon_sym_GT] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [anon_sym_GT] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(127)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(148)),
        [sym__expression] = ACTIONS(SHIFT(202)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_relational_expression] = ACTIONS(SHIFT(150)),
        [sym_template_call] = ACTIONS(SHIFT(150)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(203)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(152)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(122)),
        [sym__expression] = ACTIONS(SHIFT(201)),
        [sym_call_expression] = ACTIONS(SHIFT(125)),
        [sym_relational_expression] = ACTIONS(SHIFT(125)),
        [sym_template_call] = ACTIONS(SHIFT(125)),
        [sym_string] = ACTIONS(SHIFT(125)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(204)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(162)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(163)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(205)),
        [anon_sym_GT] = ACTIONS(SHIFT(165)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(206)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [209] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [sym_compound_statement] = ACTIONS(SHIFT(282)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(214)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_function_body, 1)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_body, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_body, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_function_body, 1)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_body, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(122)),
        [sym_initializer_clause] = ACTIONS(SHIFT(123)),
        [sym__expression] = ACTIONS(SHIFT(124)),
        [sym_call_expression] = ACTIONS(SHIFT(125)),
        [sym_relational_expression] = ACTIONS(SHIFT(125)),
        [sym_template_call] = ACTIONS(SHIFT(125)),
        [anon_sym_default] = ACTIONS(SHIFT(280)),
        [anon_sym_delete] = ACTIONS(SHIFT(280)),
        [sym_string] = ACTIONS(SHIFT(125)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [213] = {
        [sym_member_initializer] = ACTIONS(SHIFT(271)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_constructor_initializer, 1)),
        [aux_sym_constructor_initializer_repeat1] = ACTIONS(SHIFT(272)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(SHIFT(273)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_constructor_initializer, 1)),
        [sym_identifier] = ACTIONS(SHIFT(274)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [sym__block_declaration] = ACTIONS(SHIFT(215)),
        [sym_simple_declaration] = ACTIONS(SHIFT(216)),
        [sym_namespace_alias_definition] = ACTIONS(SHIFT(216)),
        [sym_scoped_identifier] = ACTIONS(SHIFT(217)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(218)),
        [sym_compound_statement] = ACTIONS(SHIFT(215)),
        [sym__statement] = ACTIONS(SHIFT(219)),
        [sym_expression_statement] = ACTIONS(SHIFT(215)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym__expression] = ACTIONS(SHIFT(220)),
        [sym_call_expression] = ACTIONS(SHIFT(221)),
        [sym_relational_expression] = ACTIONS(SHIFT(221)),
        [sym_template_call] = ACTIONS(SHIFT(221)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(222)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(223)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(224)),
        [anon_sym_namespace] = ACTIONS(SHIFT(225)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(226)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(227)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_string] = ACTIONS(SHIFT(221)),
        [sym_identifier] = ACTIONS(SHIFT(228)),
        [sym_number] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_call_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_template_call] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_string] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym__statement] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym__expression] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_call_expression] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_template_call] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_string] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_number] = ACTIONS(REDUCE(sym__block_declaration, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(230)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
        [sym_declarator] = ACTIONS(SHIFT(105)),
        [sym_direct_declarator] = ACTIONS(SHIFT(106)),
        [sym_pointer_operator] = ACTIONS(SHIFT(28)),
        [sym_init_declarator] = ACTIONS(SHIFT(268)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(109)),
        [anon_sym_STAR] = ACTIONS(SHIFT(32)),
        [anon_sym_AMP] = ACTIONS(SHIFT(33)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(SHIFT(110)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [219] = {
        [sym__block_declaration] = ACTIONS(SHIFT(215)),
        [sym_simple_declaration] = ACTIONS(SHIFT(216)),
        [sym_namespace_alias_definition] = ACTIONS(SHIFT(216)),
        [sym_scoped_identifier] = ACTIONS(SHIFT(217)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(218)),
        [sym_compound_statement] = ACTIONS(SHIFT(215)),
        [sym__statement] = ACTIONS(SHIFT(219)),
        [sym_expression_statement] = ACTIONS(SHIFT(215)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym__expression] = ACTIONS(SHIFT(220)),
        [sym_call_expression] = ACTIONS(SHIFT(221)),
        [sym_relational_expression] = ACTIONS(SHIFT(221)),
        [sym_template_call] = ACTIONS(SHIFT(221)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(222)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(267)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(224)),
        [anon_sym_namespace] = ACTIONS(SHIFT(225)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(226)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_string] = ACTIONS(SHIFT(221)),
        [sym_identifier] = ACTIONS(SHIFT(228)),
        [sym_number] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(253)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(254)),
        [anon_sym_GT] = ACTIONS(SHIFT(255)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(255)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(255)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(255)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(255)),
        [anon_sym_LT] = ACTIONS(SHIFT(255)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(5)),
        [sym_type_specifier] = ACTIONS(SHIFT(248)),
        [sym_identifier] = ACTIONS(SHIFT(14)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(247)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym__statement] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym__expression] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_template_call] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [225] = {
        [sym_identifier] = ACTIONS(SHIFT(240)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
        [sym__block_declaration] = ACTIONS(SHIFT(215)),
        [sym_simple_declaration] = ACTIONS(SHIFT(216)),
        [sym_namespace_alias_definition] = ACTIONS(SHIFT(216)),
        [sym_scoped_identifier] = ACTIONS(SHIFT(217)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(218)),
        [sym_compound_statement] = ACTIONS(SHIFT(215)),
        [sym__statement] = ACTIONS(SHIFT(219)),
        [sym_expression_statement] = ACTIONS(SHIFT(215)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym__expression] = ACTIONS(SHIFT(220)),
        [sym_call_expression] = ACTIONS(SHIFT(221)),
        [sym_relational_expression] = ACTIONS(SHIFT(221)),
        [sym_template_call] = ACTIONS(SHIFT(221)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(222)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(237)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(224)),
        [anon_sym_namespace] = ACTIONS(SHIFT(225)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_mutable] = ACTIONS(SHIFT(12)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(226)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(238)),
        [anon_sym_inline] = ACTIONS(SHIFT(13)),
        [anon_sym_virtual] = ACTIONS(SHIFT(13)),
        [anon_sym_explicit] = ACTIONS(SHIFT(13)),
        [sym_string] = ACTIONS(SHIFT(221)),
        [sym_identifier] = ACTIONS(SHIFT(228)),
        [sym_number] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [228] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(229)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(230)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(235)),
        [sym_identifier] = ACTIONS(SHIFT(236)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(129)),
        [sym_type_id] = ACTIONS(SHIFT(231)),
        [sym_type_specifier] = ACTIONS(SHIFT(131)),
        [sym__expression] = ACTIONS(SHIFT(232)),
        [sym_call_expression] = ACTIONS(SHIFT(133)),
        [sym_relational_expression] = ACTIONS(SHIFT(133)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [sym_string] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(134)),
        [sym_number] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [231] = {
        [anon_sym_GT] = ACTIONS(SHIFT(234)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(139)),
        [anon_sym_GT] = ACTIONS(SHIFT(233)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(141)),
        [anon_sym_LT] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [233] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(142)),
        [sym__expression] = ACTIONS(SHIFT(143)),
        [sym_call_expression] = ACTIONS(SHIFT(133)),
        [sym_relational_expression] = ACTIONS(SHIFT(133)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(144)),
        [sym_number] = ACTIONS(SHIFT(133)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(229)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [237] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [238] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_template_call] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_template_call] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [240] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(241)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [241] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(242)),
        [sym_identifier] = ACTIONS(SHIFT(243)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym__statement] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym__expression] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_template_call] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [243] = {
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(244)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(245)),
        [sym_identifier] = ACTIONS(SHIFT(246)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_template_call] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [246] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_template_call] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(244)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [247] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym_declarator] = ACTIONS(SHIFT(105)),
        [sym_direct_declarator] = ACTIONS(SHIFT(106)),
        [sym_pointer_operator] = ACTIONS(SHIFT(28)),
        [sym_init_declarator] = ACTIONS(SHIFT(249)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(109)),
        [anon_sym_STAR] = ACTIONS(SHIFT(32)),
        [anon_sym_AMP] = ACTIONS(SHIFT(33)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(33)),
        [sym_identifier] = ACTIONS(SHIFT(110)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(250)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(251)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(104)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [250] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(252)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym__statement] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym__expression] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_template_call] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym__statement] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym__expression] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_template_call] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_template_call] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(148)),
        [sym__expression] = ACTIONS(SHIFT(262)),
        [sym_call_expression] = ACTIONS(SHIFT(150)),
        [sym_relational_expression] = ACTIONS(SHIFT(150)),
        [sym_template_call] = ACTIONS(SHIFT(150)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(263)),
        [sym_string] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(152)),
        [sym_number] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(256)),
        [sym__expression] = ACTIONS(SHIFT(257)),
        [sym_call_expression] = ACTIONS(SHIFT(221)),
        [sym_relational_expression] = ACTIONS(SHIFT(221)),
        [sym_template_call] = ACTIONS(SHIFT(221)),
        [sym_string] = ACTIONS(SHIFT(221)),
        [sym_identifier] = ACTIONS(SHIFT(258)),
        [sym_number] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(230)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_relational_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(259)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1), SHIFT(230)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [259] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(260)),
        [sym_identifier] = ACTIONS(SHIFT(261)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [260] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [261] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(259)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [262] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(264)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(162)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(163)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(265)),
        [anon_sym_GT] = ACTIONS(SHIFT(165)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(165)),
        [anon_sym_LT] = ACTIONS(SHIFT(165)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [264] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(266)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [265] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [267] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [268] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(269)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(270)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(104)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [269] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [270] = {
        [sym__block_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_relational_expression] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_template_call] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [271] = {
        [sym_member_initializer] = ACTIONS(SHIFT(271)),
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 1)),
        [aux_sym_constructor_initializer_repeat1] = ACTIONS(SHIFT(279)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(274)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [272] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_constructor_initializer, 2)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(SHIFT(278)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_constructor_initializer, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [273] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_constructor_initializer, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_constructor_initializer, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [274] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [275] = {
        [anon_sym_initializer_list] = ACTIONS(SHIFT(276)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [276] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(277)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [277] = {
        [sym_member_initializer] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [aux_sym_constructor_initializer_repeat1] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [278] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_constructor_initializer, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_constructor_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [279] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 2)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [280] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(281)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [281] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_definition, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [282] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_function_body, 2)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_body, 2)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_body, 2)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_function_body, 2)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_body, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [283] = {
        [sym_function_body] = ACTIONS(SHIFT(287)),
        [sym_constructor_initializer] = ACTIONS(SHIFT(210)),
        [sym_compound_statement] = ACTIONS(SHIFT(211)),
        [sym_initializer] = ACTIONS(SHIFT(120)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(288)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COLON] = ACTIONS(SHIFT(213)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(214)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [284] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(285)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(286)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(104)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [285] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(103)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [286] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [287] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [288] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(122)),
        [sym_initializer_clause] = ACTIONS(SHIFT(123)),
        [sym__expression] = ACTIONS(SHIFT(124)),
        [sym_call_expression] = ACTIONS(SHIFT(125)),
        [sym_relational_expression] = ACTIONS(SHIFT(125)),
        [sym_template_call] = ACTIONS(SHIFT(125)),
        [anon_sym_default] = ACTIONS(SHIFT(289)),
        [anon_sym_delete] = ACTIONS(SHIFT(289)),
        [sym_string] = ACTIONS(SHIFT(125)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [289] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [290] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym__block_declaration] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_simple_declaration] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_namespace_alias_definition] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_friend] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_constexpr] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_thread_local] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_mutable] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_inline] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_virtual] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [anon_sym_explicit] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_definition, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [291] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_type_specifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [292] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_cpp);
