#include "tree_sitter/parser.h"

#define STATE_COUNT 321
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

static const TSSymbolMetadata ts_symbol_metadata[SYMBOL_COUNT] = {
    [sym_translation_unit] = {.visible = true, .named = true, .extra = false},
    [sym__declaration] = {.visible = false, .named = false, .extra = false},
    [sym__block_declaration] = {.visible = false, .named = false, .extra = false},
    [sym_function_definition] = {.visible = true, .named = true, .extra = false},
    [sym_simple_declaration] = {.visible = true, .named = true, .extra = false},
    [sym_namespace_alias_definition] = {.visible = true, .named = true, .extra = false},
    [sym_scoped_identifier] = {.visible = true, .named = true, .extra = false},
    [sym_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_abstract_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_direct_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_parameter_declaration] = {.visible = true, .named = true, .extra = false},
    [sym_direct_abstract_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_cv_qualifier] = {.visible = true, .named = true, .extra = false},
    [sym_type_id] = {.visible = true, .named = true, .extra = false},
    [sym_pointer_operator] = {.visible = true, .named = true, .extra = false},
    [sym_function_body] = {.visible = true, .named = true, .extra = false},
    [sym_constructor_initializer] = {.visible = true, .named = true, .extra = false},
    [sym_member_initializer] = {.visible = true, .named = true, .extra = false},
    [sym_init_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_decl_specifier] = {.visible = true, .named = true, .extra = false},
    [sym_storage_class_specifier] = {.visible = true, .named = true, .extra = false},
    [sym_type_specifier] = {.visible = true, .named = true, .extra = false},
    [sym_compound_statement] = {.visible = true, .named = true, .extra = false},
    [sym__statement] = {.visible = false, .named = false, .extra = false},
    [sym_expression_statement] = {.visible = true, .named = true, .extra = false},
    [sym_initializer] = {.visible = true, .named = true, .extra = false},
    [sym_initializer_clause] = {.visible = true, .named = true, .extra = false},
    [sym_function_specifier] = {.visible = true, .named = true, .extra = false},
    [sym__expression] = {.visible = false, .named = false, .extra = false},
    [sym_call_expression] = {.visible = true, .named = true, .extra = false},
    [sym_relational_expression] = {.visible = true, .named = true, .extra = false},
    [sym_template_call] = {.visible = true, .named = true, .extra = false},
    [aux_sym_translation_unit_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_function_definition_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_simple_declaration_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_declarator_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_direct_declarator_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_pointer_operator_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_constructor_initializer_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_compound_statement_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_call_expression_repeat1] = {.visible = false, .named = false, .extra = false},
    [ts_builtin_sym_error] = {.visible = true, .named = true, .extra = true},
    [ts_builtin_sym_end] = {.visible = false, .named = false, .extra = false},
    [anon_sym_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_default] = {.visible = true, .named = false, .extra = false},
    [anon_sym_delete] = {.visible = true, .named = false, .extra = false},
    [anon_sym_SEMI] = {.visible = true, .named = false, .extra = false},
    [anon_sym_COMMA] = {.visible = true, .named = false, .extra = false},
    [anon_sym_namespace] = {.visible = true, .named = false, .extra = false},
    [anon_sym_COLON_COLON] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LPAREN] = {.visible = true, .named = false, .extra = false},
    [anon_sym_RPAREN] = {.visible = true, .named = false, .extra = false},
    [anon_sym_const] = {.visible = true, .named = false, .extra = false},
    [anon_sym_volatile] = {.visible = true, .named = false, .extra = false},
    [anon_sym_STAR] = {.visible = true, .named = false, .extra = false},
    [anon_sym_AMP] = {.visible = true, .named = false, .extra = false},
    [anon_sym_AMP_AMP] = {.visible = true, .named = false, .extra = false},
    [anon_sym_COLON] = {.visible = true, .named = false, .extra = false},
    [anon_sym_DOT_DOT_DOT] = {.visible = true, .named = false, .extra = false},
    [anon_sym_initializer_list] = {.visible = true, .named = false, .extra = false},
    [anon_sym_friend] = {.visible = true, .named = false, .extra = false},
    [anon_sym_typedef] = {.visible = true, .named = false, .extra = false},
    [anon_sym_constexpr] = {.visible = true, .named = false, .extra = false},
    [anon_sym_register] = {.visible = true, .named = false, .extra = false},
    [anon_sym_static] = {.visible = true, .named = false, .extra = false},
    [anon_sym_thread_local] = {.visible = true, .named = false, .extra = false},
    [anon_sym_extern] = {.visible = true, .named = false, .extra = false},
    [anon_sym_mutable] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LBRACE] = {.visible = true, .named = false, .extra = false},
    [anon_sym_RBRACE] = {.visible = true, .named = false, .extra = false},
    [anon_sym_inline] = {.visible = true, .named = false, .extra = false},
    [anon_sym_virtual] = {.visible = true, .named = false, .extra = false},
    [anon_sym_explicit] = {.visible = true, .named = false, .extra = false},
    [anon_sym_GT] = {.visible = true, .named = false, .extra = false},
    [anon_sym_GT_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_EQ_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_BANG_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LT_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LT] = {.visible = true, .named = false, .extra = false},
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
            if (lookahead == '<')
                ADVANCE(100);
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
            ACCEPT_TOKEN(anon_sym_LT);
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
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 103:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 104:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(105);
            if (lookahead == '<')
                ADVANCE(100);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 105:
            if (lookahead == ':')
                ADVANCE(106);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(anon_sym_COLON_COLON);
        case 107:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 108:
            if (lookahead == '\"')
                ADVANCE(109);
            if (lookahead == '\\')
                ADVANCE(110);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(108);
            LEX_ERROR();
        case 109:
            ACCEPT_TOKEN(sym_string);
        case 110:
            if (lookahead == '\"')
                ADVANCE(111);
            if (lookahead == '\\')
                ADVANCE(110);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(108);
            LEX_ERROR();
        case 111:
            if (lookahead == '\"')
                ADVANCE(109);
            if (lookahead == '\\')
                ADVANCE(110);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(108);
            ACCEPT_TOKEN(sym_string);
        case 112:
            if (lookahead == '.')
                ADVANCE(113);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            ACCEPT_TOKEN(sym_number);
        case 113:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(114);
            LEX_ERROR();
        case 114:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(114);
            ACCEPT_TOKEN(sym_number);
        case 115:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 116:
            if (lookahead == '=')
                ADVANCE(117);
            LEX_ERROR();
        case 117:
            ACCEPT_TOKEN(anon_sym_BANG_EQ);
        case 118:
            if (lookahead == '=')
                ADVANCE(119);
            ACCEPT_TOKEN(anon_sym_LT);
        case 119:
            ACCEPT_TOKEN(anon_sym_LT_EQ);
        case 120:
            if (lookahead == '=')
                ADVANCE(121);
            LEX_ERROR();
        case 121:
            ACCEPT_TOKEN(anon_sym_EQ_EQ);
        case 122:
            if (lookahead == '=')
                ADVANCE(123);
            ACCEPT_TOKEN(anon_sym_GT);
        case 123:
            ACCEPT_TOKEN(anon_sym_GT_EQ);
        case 124:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(124);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '>')
                ADVANCE(125);
            LEX_ERROR();
        case 125:
            ACCEPT_TOKEN(anon_sym_GT);
        case 126:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '>')
                ADVANCE(125);
            LEX_ERROR();
        case 127:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 128:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(105);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 129:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 130:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 131:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(131);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 132:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(105);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 134:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 135:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(105);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 137:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'c')
                ADVANCE(143);
            if (lookahead == 'v')
                ADVANCE(148);
            LEX_ERROR();
        case 143:
            if (lookahead == 'o')
                ADVANCE(144);
            LEX_ERROR();
        case 144:
            if (lookahead == 'n')
                ADVANCE(145);
            LEX_ERROR();
        case 145:
            if (lookahead == 's')
                ADVANCE(146);
            LEX_ERROR();
        case 146:
            if (lookahead == 't')
                ADVANCE(147);
            LEX_ERROR();
        case 147:
            ACCEPT_TOKEN(anon_sym_const);
        case 148:
            if (lookahead == 'o')
                ADVANCE(149);
            LEX_ERROR();
        case 149:
            if (lookahead == 'l')
                ADVANCE(150);
            LEX_ERROR();
        case 150:
            if (lookahead == 'a')
                ADVANCE(151);
            LEX_ERROR();
        case 151:
            if (lookahead == 't')
                ADVANCE(152);
            LEX_ERROR();
        case 152:
            if (lookahead == 'i')
                ADVANCE(153);
            LEX_ERROR();
        case 153:
            if (lookahead == 'l')
                ADVANCE(154);
            LEX_ERROR();
        case 154:
            if (lookahead == 'e')
                ADVANCE(155);
            LEX_ERROR();
        case 155:
            ACCEPT_TOKEN(anon_sym_volatile);
        case 156:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(156);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(157);
            LEX_ERROR();
        case 157:
            ACCEPT_TOKEN(anon_sym_EQ);
        case 158:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(158);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(105);
            LEX_ERROR();
        case 159:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(105);
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
        case 160:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(160);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(161);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '=')
                ADVANCE(157);
            if (lookahead == '{')
                ADVANCE(163);
            LEX_ERROR();
        case 161:
            ACCEPT_TOKEN(anon_sym_COLON);
        case 162:
            ACCEPT_TOKEN(anon_sym_SEMI);
        case 163:
            ACCEPT_TOKEN(anon_sym_LBRACE);
        case 164:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(164);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(161);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '=')
                ADVANCE(157);
            if (lookahead == '{')
                ADVANCE(163);
            LEX_ERROR();
        case 165:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(165);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(162);
            LEX_ERROR();
        case 166:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(166);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 167:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(167);
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
                ADVANCE(168);
            if (lookahead == 'v')
                ADVANCE(173);
            LEX_ERROR();
        case 168:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'o')
                ADVANCE(169);
            ACCEPT_TOKEN(sym_identifier);
        case 169:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(170);
            ACCEPT_TOKEN(sym_identifier);
        case 170:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 's')
                ADVANCE(171);
            ACCEPT_TOKEN(sym_identifier);
        case 171:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(172);
            ACCEPT_TOKEN(sym_identifier);
        case 172:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_const);
        case 173:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'o')
                ADVANCE(174);
            ACCEPT_TOKEN(sym_identifier);
        case 174:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(175);
            ACCEPT_TOKEN(sym_identifier);
        case 175:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(176);
            ACCEPT_TOKEN(sym_identifier);
        case 176:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(177);
            ACCEPT_TOKEN(sym_identifier);
        case 177:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(178);
            ACCEPT_TOKEN(sym_identifier);
        case 178:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(179);
            ACCEPT_TOKEN(sym_identifier);
        case 179:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(180);
            ACCEPT_TOKEN(sym_identifier);
        case 180:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_volatile);
        case 181:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(181);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 182:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(182);
            if (lookahead == ')')
                ADVANCE(130);
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
        case 183:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(183);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 184:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(184);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 185:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(185);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(162);
            LEX_ERROR();
        case 186:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(186);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '=')
                ADVANCE(157);
            LEX_ERROR();
        case 187:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(187);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '=')
                ADVANCE(157);
            LEX_ERROR();
        case 188:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(188);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 189:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(189);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(105);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 190:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(190);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 191:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(191);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '{')
                ADVANCE(163);
            LEX_ERROR();
        case 192:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(192);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'd')
                ADVANCE(193);
            LEX_ERROR();
        case 193:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(194);
            ACCEPT_TOKEN(sym_identifier);
        case 194:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'f')
                ADVANCE(195);
            if (lookahead == 'l')
                ADVANCE(200);
            ACCEPT_TOKEN(sym_identifier);
        case 195:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(196);
            ACCEPT_TOKEN(sym_identifier);
        case 196:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'u')
                ADVANCE(197);
            ACCEPT_TOKEN(sym_identifier);
        case 197:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(198);
            ACCEPT_TOKEN(sym_identifier);
        case 198:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(199);
            ACCEPT_TOKEN(sym_identifier);
        case 199:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_default);
        case 200:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(201);
            ACCEPT_TOKEN(sym_identifier);
        case 201:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(202);
            ACCEPT_TOKEN(sym_identifier);
        case 202:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(203);
            ACCEPT_TOKEN(sym_identifier);
        case 203:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_delete);
        case 204:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(204);
            if (lookahead == '.')
                ADVANCE(205);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == '{')
                ADVANCE(163);
            LEX_ERROR();
        case 205:
            if (lookahead == '.')
                ADVANCE(206);
            LEX_ERROR();
        case 206:
            if (lookahead == '.')
                ADVANCE(207);
            LEX_ERROR();
        case 207:
            ACCEPT_TOKEN(anon_sym_DOT_DOT_DOT);
        case 208:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(208);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == ';')
                ADVANCE(162);
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
                ADVANCE(163);
            if (lookahead == '}')
                ADVANCE(209);
            LEX_ERROR();
        case 209:
            ACCEPT_TOKEN(anon_sym_RBRACE);
        case 210:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(210);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
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
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 212:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(212);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(209);
            LEX_ERROR();
        case 213:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(213);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(105);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 214:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(214);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 215:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(215);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == ':')
                ADVANCE(105);
            if (lookahead == ';')
                ADVANCE(162);
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
                ADVANCE(163);
            if (lookahead == '}')
                ADVANCE(209);
            LEX_ERROR();
        case 216:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(216);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(105);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            LEX_ERROR();
        case 217:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(217);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(120);
            if (lookahead == '>')
                ADVANCE(122);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            LEX_ERROR();
        case 218:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(218);
            if (lookahead == '.')
                ADVANCE(205);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '{')
                ADVANCE(163);
            LEX_ERROR();
        case 219:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(219);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'i')
                ADVANCE(220);
            LEX_ERROR();
        case 220:
            if (lookahead == 'n')
                ADVANCE(221);
            LEX_ERROR();
        case 221:
            if (lookahead == 'i')
                ADVANCE(222);
            LEX_ERROR();
        case 222:
            if (lookahead == 't')
                ADVANCE(223);
            LEX_ERROR();
        case 223:
            if (lookahead == 'i')
                ADVANCE(224);
            LEX_ERROR();
        case 224:
            if (lookahead == 'a')
                ADVANCE(225);
            LEX_ERROR();
        case 225:
            if (lookahead == 'l')
                ADVANCE(226);
            LEX_ERROR();
        case 226:
            if (lookahead == 'i')
                ADVANCE(227);
            LEX_ERROR();
        case 227:
            if (lookahead == 'z')
                ADVANCE(228);
            LEX_ERROR();
        case 228:
            if (lookahead == 'e')
                ADVANCE(229);
            LEX_ERROR();
        case 229:
            if (lookahead == 'r')
                ADVANCE(230);
            LEX_ERROR();
        case 230:
            if (lookahead == '_')
                ADVANCE(231);
            LEX_ERROR();
        case 231:
            if (lookahead == 'l')
                ADVANCE(232);
            LEX_ERROR();
        case 232:
            if (lookahead == 'i')
                ADVANCE(233);
            LEX_ERROR();
        case 233:
            if (lookahead == 's')
                ADVANCE(234);
            LEX_ERROR();
        case 234:
            if (lookahead == 't')
                ADVANCE(235);
            LEX_ERROR();
        case 235:
            ACCEPT_TOKEN(anon_sym_initializer_list);
        case 236:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(236);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '.')
                ADVANCE(205);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == ':')
                ADVANCE(237);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(238);
            if (lookahead == '>')
                ADVANCE(122);
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
                ADVANCE(239);
            if (lookahead == 'd')
                ADVANCE(193);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(244);
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
                ADVANCE(260);
            if (lookahead == '{')
                ADVANCE(163);
            if (lookahead == '}')
                ADVANCE(209);
            LEX_ERROR();
        case 237:
            if (lookahead == ':')
                ADVANCE(106);
            ACCEPT_TOKEN(anon_sym_COLON);
        case 238:
            if (lookahead == '=')
                ADVANCE(121);
            ACCEPT_TOKEN(anon_sym_EQ);
        case 239:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'o')
                ADVANCE(240);
            ACCEPT_TOKEN(sym_identifier);
        case 240:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(241);
            ACCEPT_TOKEN(sym_identifier);
        case 241:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 's')
                ADVANCE(242);
            ACCEPT_TOKEN(sym_identifier);
        case 242:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(243);
            ACCEPT_TOKEN(sym_identifier);
        case 243:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(11);
            ACCEPT_TOKEN(anon_sym_const);
        case 244:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'n')
                ADVANCE(245);
            ACCEPT_TOKEN(sym_identifier);
        case 245:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                (lookahead == 'j') ||
                (lookahead == 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(246);
            if (lookahead == 'l')
                ADVANCE(35);
            ACCEPT_TOKEN(sym_identifier);
        case 246:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(247);
            ACCEPT_TOKEN(sym_identifier);
        case 247:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(248);
            ACCEPT_TOKEN(sym_identifier);
        case 248:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'a')
                ADVANCE(249);
            ACCEPT_TOKEN(sym_identifier);
        case 249:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(250);
            ACCEPT_TOKEN(sym_identifier);
        case 250:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(251);
            ACCEPT_TOKEN(sym_identifier);
        case 251:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'y'))
                ADVANCE(5);
            if (lookahead == 'z')
                ADVANCE(252);
            ACCEPT_TOKEN(sym_identifier);
        case 252:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'e')
                ADVANCE(253);
            ACCEPT_TOKEN(sym_identifier);
        case 253:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'r')
                ADVANCE(254);
            ACCEPT_TOKEN(sym_identifier);
        case 254:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == '_')
                ADVANCE(255);
            ACCEPT_TOKEN(sym_identifier);
        case 255:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'l')
                ADVANCE(256);
            ACCEPT_TOKEN(sym_identifier);
        case 256:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 'i')
                ADVANCE(257);
            ACCEPT_TOKEN(sym_identifier);
        case 257:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 's')
                ADVANCE(258);
            ACCEPT_TOKEN(sym_identifier);
        case 258:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(259);
            ACCEPT_TOKEN(sym_identifier);
        case 259:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(5);
            ACCEPT_TOKEN(anon_sym_initializer_list);
        case 260:
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
                ADVANCE(174);
            ACCEPT_TOKEN(sym_identifier);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(236);
            if (lookahead == '!')
                ADVANCE(116);
            if (lookahead == '\"')
                ADVANCE(108);
            if (lookahead == '&')
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(98);
            if (lookahead == ')')
                ADVANCE(130);
            if (lookahead == '*')
                ADVANCE(99);
            if (lookahead == ',')
                ADVANCE(135);
            if (lookahead == '.')
                ADVANCE(205);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(112);
            if (lookahead == ':')
                ADVANCE(237);
            if (lookahead == ';')
                ADVANCE(162);
            if (lookahead == '<')
                ADVANCE(118);
            if (lookahead == '=')
                ADVANCE(238);
            if (lookahead == '>')
                ADVANCE(122);
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
                ADVANCE(239);
            if (lookahead == 'd')
                ADVANCE(193);
            if (lookahead == 'e')
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(27);
            if (lookahead == 'i')
                ADVANCE(244);
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
                ADVANCE(260);
            if (lookahead == '{')
                ADVANCE(163);
            if (lookahead == '}')
                ADVANCE(209);
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
    [6] = 101,
    [7] = 101,
    [8] = 102,
    [9] = 102,
    [10] = 94,
    [11] = 103,
    [12] = 103,
    [13] = 101,
    [14] = 101,
    [15] = 104,
    [16] = 103,
    [17] = 107,
    [18] = 115,
    [19] = 124,
    [20] = 126,
    [21] = 127,
    [22] = 127,
    [23] = 115,
    [24] = 128,
    [25] = 103,
    [26] = 107,
    [27] = 124,
    [28] = 127,
    [29] = 129,
    [30] = 131,
    [31] = 107,
    [32] = 127,
    [33] = 127,
    [34] = 127,
    [35] = 132,
    [36] = 103,
    [37] = 107,
    [38] = 124,
    [39] = 127,
    [40] = 133,
    [41] = 127,
    [42] = 127,
    [43] = 132,
    [44] = 134,
    [45] = 134,
    [46] = 134,
    [47] = 134,
    [48] = 127,
    [49] = 136,
    [50] = 103,
    [51] = 107,
    [52] = 124,
    [53] = 127,
    [54] = 137,
    [55] = 134,
    [56] = 134,
    [57] = 136,
    [58] = 138,
    [59] = 107,
    [60] = 129,
    [61] = 127,
    [62] = 107,
    [63] = 134,
    [64] = 134,
    [65] = 134,
    [66] = 138,
    [67] = 134,
    [68] = 134,
    [69] = 134,
    [70] = 138,
    [71] = 127,
    [72] = 115,
    [73] = 115,
    [74] = 128,
    [75] = 139,
    [76] = 124,
    [77] = 124,
    [78] = 140,
    [79] = 141,
    [80] = 140,
    [81] = 142,
    [82] = 140,
    [83] = 142,
    [84] = 140,
    [85] = 142,
    [86] = 140,
    [87] = 138,
    [88] = 138,
    [89] = 141,
    [90] = 140,
    [91] = 138,
    [92] = 138,
    [93] = 138,
    [94] = 124,
    [95] = 124,
    [96] = 141,
    [97] = 102,
    [98] = 95,
    [99] = 104,
    [100] = 156,
    [101] = 103,
    [102] = 1,
    [103] = 158,
    [104] = 103,
    [105] = 1,
    [106] = 159,
    [107] = 102,
    [108] = 160,
    [109] = 164,
    [110] = 102,
    [111] = 165,
    [112] = 166,
    [113] = 102,
    [114] = 167,
    [115] = 102,
    [116] = 164,
    [117] = 167,
    [118] = 102,
    [119] = 167,
    [120] = 102,
    [121] = 138,
    [122] = 181,
    [123] = 166,
    [124] = 102,
    [125] = 181,
    [126] = 138,
    [127] = 181,
    [128] = 181,
    [129] = 182,
    [130] = 95,
    [131] = 183,
    [132] = 102,
    [133] = 102,
    [134] = 103,
    [135] = 104,
    [136] = 103,
    [137] = 107,
    [138] = 124,
    [139] = 127,
    [140] = 139,
    [141] = 102,
    [142] = 95,
    [143] = 104,
    [144] = 102,
    [145] = 183,
    [146] = 184,
    [147] = 183,
    [148] = 102,
    [149] = 166,
    [150] = 102,
    [151] = 167,
    [152] = 102,
    [153] = 184,
    [154] = 167,
    [155] = 102,
    [156] = 167,
    [157] = 102,
    [158] = 138,
    [159] = 138,
    [160] = 166,
    [161] = 102,
    [162] = 183,
    [163] = 184,
    [164] = 184,
    [165] = 183,
    [166] = 182,
    [167] = 183,
    [168] = 138,
    [169] = 101,
    [170] = 184,
    [171] = 183,
    [172] = 138,
    [173] = 184,
    [174] = 166,
    [175] = 183,
    [176] = 138,
    [177] = 181,
    [178] = 181,
    [179] = 164,
    [180] = 164,
    [181] = 182,
    [182] = 183,
    [183] = 138,
    [184] = 164,
    [185] = 164,
    [186] = 185,
    [187] = 1,
    [188] = 102,
    [189] = 186,
    [190] = 187,
    [191] = 165,
    [192] = 166,
    [193] = 102,
    [194] = 187,
    [195] = 138,
    [196] = 187,
    [197] = 187,
    [198] = 182,
    [199] = 183,
    [200] = 138,
    [201] = 187,
    [202] = 187,
    [203] = 185,
    [204] = 165,
    [205] = 107,
    [206] = 188,
    [207] = 165,
    [208] = 188,
    [209] = 188,
    [210] = 188,
    [211] = 189,
    [212] = 103,
    [213] = 107,
    [214] = 124,
    [215] = 127,
    [216] = 190,
    [217] = 188,
    [218] = 188,
    [219] = 189,
    [220] = 129,
    [221] = 107,
    [222] = 188,
    [223] = 134,
    [224] = 188,
    [225] = 138,
    [226] = 188,
    [227] = 188,
    [228] = 1,
    [229] = 166,
    [230] = 1,
    [231] = 191,
    [232] = 1,
    [233] = 192,
    [234] = 204,
    [235] = 208,
    [236] = 208,
    [237] = 208,
    [238] = 210,
    [239] = 102,
    [240] = 208,
    [241] = 211,
    [242] = 211,
    [243] = 210,
    [244] = 103,
    [245] = 212,
    [246] = 208,
    [247] = 103,
    [248] = 208,
    [249] = 1,
    [250] = 213,
    [251] = 103,
    [252] = 107,
    [253] = 124,
    [254] = 127,
    [255] = 214,
    [256] = 210,
    [257] = 210,
    [258] = 213,
    [259] = 212,
    [260] = 208,
    [261] = 208,
    [262] = 156,
    [263] = 103,
    [264] = 208,
    [265] = 158,
    [266] = 103,
    [267] = 208,
    [268] = 215,
    [269] = 1,
    [270] = 102,
    [271] = 165,
    [272] = 185,
    [273] = 208,
    [274] = 208,
    [275] = 208,
    [276] = 129,
    [277] = 107,
    [278] = 211,
    [279] = 211,
    [280] = 211,
    [281] = 216,
    [282] = 103,
    [283] = 107,
    [284] = 124,
    [285] = 127,
    [286] = 217,
    [287] = 211,
    [288] = 211,
    [289] = 216,
    [290] = 134,
    [291] = 211,
    [292] = 138,
    [293] = 211,
    [294] = 211,
    [295] = 212,
    [296] = 165,
    [297] = 185,
    [298] = 208,
    [299] = 204,
    [300] = 218,
    [301] = 191,
    [302] = 141,
    [303] = 219,
    [304] = 138,
    [305] = 204,
    [306] = 191,
    [307] = 218,
    [308] = 185,
    [309] = 1,
    [310] = 1,
    [311] = 160,
    [312] = 165,
    [313] = 185,
    [314] = 1,
    [315] = 1,
    [316] = 192,
    [317] = 185,
    [318] = 1,
    [319] = 103,
    [320] = 94,
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
        [sym_template_call] = ACTIONS(SHIFT(9)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(10)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(11)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_translation_unit, 0)),
        [anon_sym_namespace] = ACTIONS(SHIFT(12)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
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
        [sym_template_call] = ACTIONS(SHIFT(9)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(320)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(11)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 1)),
        [anon_sym_namespace] = ACTIONS(SHIFT(12)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
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
        [sym_template_call] = ACTIONS(REDUCE(sym__declaration, 1)),
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
        [sym_template_call] = ACTIONS(REDUCE(sym__block_declaration, 1)),
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
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LT] = ACTIONS(SHIFT(17)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym_template_call] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(319)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [7] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
        [sym_template_call] = ACTIONS(REDUCE(sym_decl_specifier, 1)),
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
        [sym_declarator] = ACTIONS(SHIFT(311)),
        [sym_direct_declarator] = ACTIONS(SHIFT(109)),
        [sym_pointer_operator] = ACTIONS(SHIFT(110)),
        [sym_init_declarator] = ACTIONS(SHIFT(312)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(112)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(113)),
        [anon_sym_STAR] = ACTIONS(SHIFT(114)),
        [anon_sym_AMP] = ACTIONS(SHIFT(115)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(116)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_translation_unit, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(5)),
        [sym_type_specifier] = ACTIONS(SHIFT(107)),
        [sym_template_call] = ACTIONS(SHIFT(9)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym_identifier] = ACTIONS(SHIFT(100)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_template_call] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
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
    [14] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_decl_specifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_type_specifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_function_specifier] = ACTIONS(REDUCE(sym_function_specifier, 1)),
        [sym_template_call] = ACTIONS(REDUCE(sym_function_specifier, 1)),
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
    [15] = {
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(16)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LT] = ACTIONS(SHIFT(17)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(98)),
        [sym_identifier] = ACTIONS(SHIFT(99)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(18)),
        [sym_type_id] = ACTIONS(SHIFT(19)),
        [sym_type_specifier] = ACTIONS(SHIFT(20)),
        [sym__expression] = ACTIONS(SHIFT(21)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(23)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [sym_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [anon_sym_GT] = ACTIONS(SHIFT(97)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [sym_abstract_declarator] = ACTIONS(SHIFT(76)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(77)),
        [sym_pointer_operator] = ACTIONS(SHIFT(78)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(79)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_AMP] = ACTIONS(SHIFT(82)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(82)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_type_id, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(29)),
        [anon_sym_GT] = ACTIONS(SHIFT(75)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT] = ACTIONS(SHIFT(31)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [sym_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [sym_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(25)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(26)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(73)),
        [sym_identifier] = ACTIONS(SHIFT(74)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(18)),
        [sym_type_id] = ACTIONS(SHIFT(27)),
        [sym_type_specifier] = ACTIONS(SHIFT(20)),
        [sym__expression] = ACTIONS(SHIFT(28)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(23)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [anon_sym_GT] = ACTIONS(SHIFT(72)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(29)),
        [anon_sym_GT] = ACTIONS(SHIFT(30)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT] = ACTIONS(SHIFT(31)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(44)),
        [sym__expression] = ACTIONS(SHIFT(45)),
        [sym_call_expression] = ACTIONS(SHIFT(46)),
        [sym_relational_expression] = ACTIONS(SHIFT(46)),
        [sym_template_call] = ACTIONS(SHIFT(47)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(48)),
        [sym_string] = ACTIONS(SHIFT(46)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_number] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(32)),
        [sym_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym__expression] = ACTIONS(SHIFT(33)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(34)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(32)),
        [sym__expression] = ACTIONS(SHIFT(33)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(34)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(37)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [33] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [34] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [35] = {
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(36)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(37)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [36] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(42)),
        [sym_identifier] = ACTIONS(SHIFT(43)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [37] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(18)),
        [sym_type_id] = ACTIONS(SHIFT(38)),
        [sym_type_specifier] = ACTIONS(SHIFT(20)),
        [sym__expression] = ACTIONS(SHIFT(39)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(23)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [38] = {
        [anon_sym_GT] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [39] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(29)),
        [anon_sym_GT] = ACTIONS(SHIFT(40)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT] = ACTIONS(SHIFT(31)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [40] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(32)),
        [sym__expression] = ACTIONS(SHIFT(33)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(34)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [41] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [42] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [43] = {
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(36)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [44] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(51)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [45] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(58)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(60)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(61)),
        [anon_sym_GT] = ACTIONS(SHIFT(62)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT] = ACTIONS(SHIFT(62)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [46] = {
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
    [47] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [48] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [49] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(50)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(51)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [50] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(56)),
        [sym_identifier] = ACTIONS(SHIFT(57)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [51] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(18)),
        [sym_type_id] = ACTIONS(SHIFT(52)),
        [sym_type_specifier] = ACTIONS(SHIFT(20)),
        [sym__expression] = ACTIONS(SHIFT(53)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(23)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [52] = {
        [anon_sym_GT] = ACTIONS(SHIFT(55)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [53] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(29)),
        [anon_sym_GT] = ACTIONS(SHIFT(54)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT] = ACTIONS(SHIFT(31)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [54] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(32)),
        [sym__expression] = ACTIONS(SHIFT(33)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(34)),
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [55] = {
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
    [56] = {
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
    [57] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(50)),
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
    [58] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(71)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [59] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(44)),
        [sym__expression] = ACTIONS(SHIFT(69)),
        [sym_call_expression] = ACTIONS(SHIFT(46)),
        [sym_relational_expression] = ACTIONS(SHIFT(46)),
        [sym_template_call] = ACTIONS(SHIFT(47)),
        [sym_string] = ACTIONS(SHIFT(46)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_number] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [60] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(44)),
        [sym__expression] = ACTIONS(SHIFT(64)),
        [sym_call_expression] = ACTIONS(SHIFT(46)),
        [sym_relational_expression] = ACTIONS(SHIFT(46)),
        [sym_template_call] = ACTIONS(SHIFT(47)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(65)),
        [sym_string] = ACTIONS(SHIFT(46)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_number] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [61] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [62] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(44)),
        [sym__expression] = ACTIONS(SHIFT(63)),
        [sym_call_expression] = ACTIONS(SHIFT(46)),
        [sym_relational_expression] = ACTIONS(SHIFT(46)),
        [sym_template_call] = ACTIONS(SHIFT(47)),
        [sym_string] = ACTIONS(SHIFT(46)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_number] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [63] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [64] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(66)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(60)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(67)),
        [anon_sym_GT] = ACTIONS(SHIFT(62)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT] = ACTIONS(SHIFT(62)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [65] = {
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
    [66] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(68)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [67] = {
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
    [68] = {
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
    [69] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(70)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(60)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [anon_sym_GT] = ACTIONS(SHIFT(62)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT] = ACTIONS(SHIFT(62)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [70] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [71] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [72] = {
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
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
    [74] = {
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(25)),
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
    [75] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(32)),
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_init_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym__expression] = ACTIONS(SHIFT(33)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(34)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4), SHIFT(35)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [anon_sym_GT] = ACTIONS(REDUCE(sym_type_id, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [anon_sym_GT] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer_operator] = ACTIONS(SHIFT(78)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(96)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_AMP] = ACTIONS(SHIFT(82)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(95)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(80)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [80] = {
        [sym_abstract_declarator] = ACTIONS(SHIFT(87)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(88)),
        [sym_pointer_operator] = ACTIONS(SHIFT(78)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(89)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_AMP] = ACTIONS(SHIFT(82)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(83)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(84)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(85)),
        [anon_sym_volatile] = ACTIONS(SHIFT(85)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [82] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(83)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(86)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(85)),
        [anon_sym_volatile] = ACTIONS(SHIFT(85)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
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
    [86] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(94)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [sym_abstract_declarator] = ACTIONS(SHIFT(91)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(88)),
        [sym_pointer_operator] = ACTIONS(SHIFT(78)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(89)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(90)),
        [anon_sym_STAR] = ACTIONS(SHIFT(81)),
        [anon_sym_AMP] = ACTIONS(SHIFT(82)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(82)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [anon_sym_GT] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [anon_sym_GT] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [99] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(16)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(102)),
        [sym_identifier] = ACTIONS(SHIFT(103)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_namespace_alias_definition, 4)),
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
    [103] = {
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(104)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(105)),
        [sym_identifier] = ACTIONS(SHIFT(106)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
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
    [106] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_function_definition_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_namespace] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(104)),
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
    [107] = {
        [sym_declarator] = ACTIONS(SHIFT(108)),
        [sym_direct_declarator] = ACTIONS(SHIFT(109)),
        [sym_pointer_operator] = ACTIONS(SHIFT(110)),
        [sym_init_declarator] = ACTIONS(SHIFT(111)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(112)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(113)),
        [anon_sym_STAR] = ACTIONS(SHIFT(114)),
        [anon_sym_AMP] = ACTIONS(SHIFT(115)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(116)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [108] = {
        [sym_function_body] = ACTIONS(SHIFT(230)),
        [sym_constructor_initializer] = ACTIONS(SHIFT(231)),
        [sym_compound_statement] = ACTIONS(SHIFT(232)),
        [sym_initializer] = ACTIONS(SHIFT(204)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(233)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COLON] = ACTIONS(SHIFT(234)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [sym_function_body] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_constructor_initializer] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_initializer] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(181)),
        [anon_sym_COLON] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer_operator] = ACTIONS(SHIFT(110)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(229)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(114)),
        [anon_sym_AMP] = ACTIONS(SHIFT(115)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(186)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(187)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(188)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(180)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(113)),
        [sym_identifier] = ACTIONS(SHIFT(116)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
        [sym_declarator] = ACTIONS(SHIFT(121)),
        [sym_direct_declarator] = ACTIONS(SHIFT(122)),
        [sym_pointer_operator] = ACTIONS(SHIFT(110)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(123)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(124)),
        [anon_sym_STAR] = ACTIONS(SHIFT(114)),
        [anon_sym_AMP] = ACTIONS(SHIFT(115)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(117)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(118)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(119)),
        [anon_sym_volatile] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
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
    [116] = {
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
    [117] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(117)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(120)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(119)),
        [anon_sym_volatile] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
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
    [119] = {
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
    [120] = {
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
    [121] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(179)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [122] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(129)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [123] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(128)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(124)),
        [sym_identifier] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [124] = {
        [sym_declarator] = ACTIONS(SHIFT(126)),
        [sym_direct_declarator] = ACTIONS(SHIFT(122)),
        [sym_pointer_operator] = ACTIONS(SHIFT(110)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(123)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(124)),
        [anon_sym_STAR] = ACTIONS(SHIFT(114)),
        [anon_sym_AMP] = ACTIONS(SHIFT(115)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [125] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(127)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(129)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(130)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(131)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(132)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(134)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LT] = ACTIONS(SHIFT(137)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [131] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(176)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(177)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
        [sym_declarator] = ACTIONS(SHIFT(175)),
        [sym_abstract_declarator] = ACTIONS(SHIFT(175)),
        [sym_direct_declarator] = ACTIONS(SHIFT(146)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(147)),
        [sym_pointer_operator] = ACTIONS(SHIFT(148)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(149)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(150)),
        [anon_sym_STAR] = ACTIONS(SHIFT(151)),
        [anon_sym_AMP] = ACTIONS(SHIFT(152)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(152)),
        [sym_identifier] = ACTIONS(SHIFT(153)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [133] = {
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(130)),
        [sym_type_specifier] = ACTIONS(SHIFT(144)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [sym_identifier] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(136)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_LT] = ACTIONS(SHIFT(137)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(142)),
        [sym_identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(18)),
        [sym_type_id] = ACTIONS(SHIFT(138)),
        [sym_type_specifier] = ACTIONS(SHIFT(20)),
        [sym__expression] = ACTIONS(SHIFT(139)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(23)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [anon_sym_GT] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [139] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(29)),
        [anon_sym_GT] = ACTIONS(SHIFT(140)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT] = ACTIONS(SHIFT(31)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [140] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(32)),
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym__expression] = ACTIONS(SHIFT(33)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(34)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4), SHIFT(35)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
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
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(136)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [144] = {
        [sym_declarator] = ACTIONS(SHIFT(145)),
        [sym_abstract_declarator] = ACTIONS(SHIFT(145)),
        [sym_direct_declarator] = ACTIONS(SHIFT(146)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(147)),
        [sym_pointer_operator] = ACTIONS(SHIFT(148)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(149)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(150)),
        [anon_sym_STAR] = ACTIONS(SHIFT(151)),
        [anon_sym_AMP] = ACTIONS(SHIFT(152)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(152)),
        [sym_identifier] = ACTIONS(SHIFT(153)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [145] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(166)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_pointer_operator] = ACTIONS(SHIFT(148)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(174)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(151)),
        [anon_sym_AMP] = ACTIONS(SHIFT(152)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(152)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(164)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(165)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(150)),
        [sym_identifier] = ACTIONS(SHIFT(153)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [sym_declarator] = ACTIONS(SHIFT(158)),
        [sym_abstract_declarator] = ACTIONS(SHIFT(159)),
        [sym_direct_declarator] = ACTIONS(SHIFT(122)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(88)),
        [sym_pointer_operator] = ACTIONS(SHIFT(148)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(160)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161)),
        [anon_sym_STAR] = ACTIONS(SHIFT(151)),
        [anon_sym_AMP] = ACTIONS(SHIFT(152)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(152)),
        [sym_identifier] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(154)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(155)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(156)),
        [anon_sym_volatile] = ACTIONS(SHIFT(156)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_operator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
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
    [153] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_cv_qualifier] = ACTIONS(SHIFT(154)),
        [sym_pointer_operator] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [aux_sym_pointer_operator_repeat1] = ACTIONS(SHIFT(157)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(156)),
        [anon_sym_volatile] = ACTIONS(SHIFT(156)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_pointer_operator_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
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
    [156] = {
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
    [157] = {
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
    [158] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(163)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(162)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(128)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161)),
        [sym_identifier] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [sym_declarator] = ACTIONS(SHIFT(126)),
        [sym_abstract_declarator] = ACTIONS(SHIFT(91)),
        [sym_direct_declarator] = ACTIONS(SHIFT(122)),
        [sym_direct_abstract_declarator] = ACTIONS(SHIFT(88)),
        [sym_pointer_operator] = ACTIONS(SHIFT(148)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(160)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161)),
        [anon_sym_STAR] = ACTIONS(SHIFT(151)),
        [anon_sym_AMP] = ACTIONS(SHIFT(152)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(152)),
        [sym_identifier] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_abstract_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(166)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(130)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(167)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(132)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(134)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(163)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(168)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(173)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(130)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(171)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(132)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(134)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(172)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_direct_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [172] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_direct_declarator_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_direct_abstract_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(178)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
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
    [180] = {
        [sym_function_body] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_constructor_initializer] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_initializer] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(181)),
        [anon_sym_COLON] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(130)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(182)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(132)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(134)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(179)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(183)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(184)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(185)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
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
    [185] = {
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
    [186] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(228)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_simple_declaration, 4)),
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
    [188] = {
        [sym_declarator] = ACTIONS(SHIFT(189)),
        [sym_direct_declarator] = ACTIONS(SHIFT(190)),
        [sym_pointer_operator] = ACTIONS(SHIFT(110)),
        [sym_init_declarator] = ACTIONS(SHIFT(191)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(192)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(193)),
        [anon_sym_STAR] = ACTIONS(SHIFT(114)),
        [anon_sym_AMP] = ACTIONS(SHIFT(115)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [sym_initializer] = ACTIONS(SHIFT(204)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(205)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_declarator, 1)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(198)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(203)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_simple_declaration_repeat1, 2)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(188)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [sym_direct_declarator] = ACTIONS(SHIFT(197)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(193)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [sym_declarator] = ACTIONS(SHIFT(195)),
        [sym_direct_declarator] = ACTIONS(SHIFT(122)),
        [sym_pointer_operator] = ACTIONS(SHIFT(110)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(123)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(124)),
        [anon_sym_STAR] = ACTIONS(SHIFT(114)),
        [anon_sym_AMP] = ACTIONS(SHIFT(115)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(196)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_declarator, 2)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_declarator, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(198)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(130)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(199)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(132)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym_template_call] = ACTIONS(SHIFT(133)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(134)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(196)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(135)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [aux_sym_direct_declarator_repeat1] = ACTIONS(SHIFT(200)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(169)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(202)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_direct_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_simple_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(206)),
        [sym_initializer_clause] = ACTIONS(SHIFT(207)),
        [sym__expression] = ACTIONS(SHIFT(208)),
        [sym_call_expression] = ACTIONS(SHIFT(209)),
        [sym_relational_expression] = ACTIONS(SHIFT(209)),
        [sym_template_call] = ACTIONS(SHIFT(210)),
        [sym_string] = ACTIONS(SHIFT(209)),
        [sym_identifier] = ACTIONS(SHIFT(211)),
        [sym_number] = ACTIONS(SHIFT(209)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(213)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer_clause, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer_clause, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_clause, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(220)),
        [anon_sym_GT] = ACTIONS(SHIFT(221)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(221)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(221)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(221)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(221)),
        [anon_sym_LT] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [209] = {
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
    [210] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(212)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(213)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(218)),
        [sym_identifier] = ACTIONS(SHIFT(219)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [213] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(18)),
        [sym_type_id] = ACTIONS(SHIFT(214)),
        [sym_type_specifier] = ACTIONS(SHIFT(20)),
        [sym__expression] = ACTIONS(SHIFT(215)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(23)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [anon_sym_GT] = ACTIONS(SHIFT(217)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(29)),
        [anon_sym_GT] = ACTIONS(SHIFT(216)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT] = ACTIONS(SHIFT(31)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(32)),
        [sym__expression] = ACTIONS(SHIFT(33)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(34)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
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
    [218] = {
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
    [219] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(212)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(44)),
        [sym__expression] = ACTIONS(SHIFT(223)),
        [sym_call_expression] = ACTIONS(SHIFT(46)),
        [sym_relational_expression] = ACTIONS(SHIFT(46)),
        [sym_template_call] = ACTIONS(SHIFT(47)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(224)),
        [sym_string] = ACTIONS(SHIFT(46)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_number] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(206)),
        [sym__expression] = ACTIONS(SHIFT(222)),
        [sym_call_expression] = ACTIONS(SHIFT(209)),
        [sym_relational_expression] = ACTIONS(SHIFT(209)),
        [sym_template_call] = ACTIONS(SHIFT(210)),
        [sym_string] = ACTIONS(SHIFT(209)),
        [sym_identifier] = ACTIONS(SHIFT(211)),
        [sym_number] = ACTIONS(SHIFT(209)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(225)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(60)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(226)),
        [anon_sym_GT] = ACTIONS(SHIFT(62)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT] = ACTIONS(SHIFT(62)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
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
    [225] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(227)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
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
    [227] = {
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
    [228] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_simple_declaration, 5)),
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
    [229] = {
        [sym_direct_declarator] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_function_definition, 4)),
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
    [231] = {
        [sym_compound_statement] = ACTIONS(SHIFT(310)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_function_body, 1)),
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
    [233] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(206)),
        [sym_initializer_clause] = ACTIONS(SHIFT(207)),
        [sym__expression] = ACTIONS(SHIFT(208)),
        [sym_call_expression] = ACTIONS(SHIFT(209)),
        [sym_relational_expression] = ACTIONS(SHIFT(209)),
        [sym_template_call] = ACTIONS(SHIFT(210)),
        [anon_sym_default] = ACTIONS(SHIFT(308)),
        [anon_sym_delete] = ACTIONS(SHIFT(308)),
        [sym_string] = ACTIONS(SHIFT(209)),
        [sym_identifier] = ACTIONS(SHIFT(211)),
        [sym_number] = ACTIONS(SHIFT(209)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [sym_member_initializer] = ACTIONS(SHIFT(299)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_constructor_initializer, 1)),
        [aux_sym_constructor_initializer_repeat1] = ACTIONS(SHIFT(300)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(SHIFT(301)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_constructor_initializer, 1)),
        [sym_identifier] = ACTIONS(SHIFT(302)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [sym__block_declaration] = ACTIONS(SHIFT(236)),
        [sym_simple_declaration] = ACTIONS(SHIFT(237)),
        [sym_namespace_alias_definition] = ACTIONS(SHIFT(237)),
        [sym_scoped_identifier] = ACTIONS(SHIFT(238)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(239)),
        [sym_compound_statement] = ACTIONS(SHIFT(236)),
        [sym__statement] = ACTIONS(SHIFT(240)),
        [sym_expression_statement] = ACTIONS(SHIFT(236)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym__expression] = ACTIONS(SHIFT(241)),
        [sym_call_expression] = ACTIONS(SHIFT(242)),
        [sym_relational_expression] = ACTIONS(SHIFT(242)),
        [sym_template_call] = ACTIONS(SHIFT(243)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(244)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(245)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(246)),
        [anon_sym_namespace] = ACTIONS(SHIFT(247)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(248)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(249)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_string] = ACTIONS(SHIFT(242)),
        [sym_identifier] = ACTIONS(SHIFT(250)),
        [sym_number] = ACTIONS(SHIFT(242)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
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
    [237] = {
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
    [238] = {
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(252)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
        [sym_declarator] = ACTIONS(SHIFT(189)),
        [sym_direct_declarator] = ACTIONS(SHIFT(190)),
        [sym_pointer_operator] = ACTIONS(SHIFT(110)),
        [sym_init_declarator] = ACTIONS(SHIFT(296)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(192)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(193)),
        [anon_sym_STAR] = ACTIONS(SHIFT(114)),
        [anon_sym_AMP] = ACTIONS(SHIFT(115)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [240] = {
        [sym__block_declaration] = ACTIONS(SHIFT(236)),
        [sym_simple_declaration] = ACTIONS(SHIFT(237)),
        [sym_namespace_alias_definition] = ACTIONS(SHIFT(237)),
        [sym_scoped_identifier] = ACTIONS(SHIFT(238)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(239)),
        [sym_compound_statement] = ACTIONS(SHIFT(236)),
        [sym__statement] = ACTIONS(SHIFT(240)),
        [sym_expression_statement] = ACTIONS(SHIFT(236)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym__expression] = ACTIONS(SHIFT(241)),
        [sym_call_expression] = ACTIONS(SHIFT(242)),
        [sym_relational_expression] = ACTIONS(SHIFT(242)),
        [sym_template_call] = ACTIONS(SHIFT(243)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(244)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(295)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(246)),
        [anon_sym_namespace] = ACTIONS(SHIFT(247)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(248)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_string] = ACTIONS(SHIFT(242)),
        [sym_identifier] = ACTIONS(SHIFT(250)),
        [sym_number] = ACTIONS(SHIFT(242)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [241] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(275)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(276)),
        [anon_sym_GT] = ACTIONS(SHIFT(277)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(277)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(277)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(277)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(277)),
        [anon_sym_LT] = ACTIONS(SHIFT(277)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
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
    [243] = {
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(5)),
        [sym_type_specifier] = ACTIONS(SHIFT(270)),
        [sym_template_call] = ACTIONS(SHIFT(9)),
        [sym_identifier] = ACTIONS(SHIFT(15)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(269)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [246] = {
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
    [247] = {
        [sym_identifier] = ACTIONS(SHIFT(262)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym__block_declaration] = ACTIONS(SHIFT(236)),
        [sym_simple_declaration] = ACTIONS(SHIFT(237)),
        [sym_namespace_alias_definition] = ACTIONS(SHIFT(237)),
        [sym_scoped_identifier] = ACTIONS(SHIFT(238)),
        [sym_decl_specifier] = ACTIONS(SHIFT(6)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(7)),
        [sym_type_specifier] = ACTIONS(SHIFT(239)),
        [sym_compound_statement] = ACTIONS(SHIFT(236)),
        [sym__statement] = ACTIONS(SHIFT(240)),
        [sym_expression_statement] = ACTIONS(SHIFT(236)),
        [sym_function_specifier] = ACTIONS(SHIFT(7)),
        [sym__expression] = ACTIONS(SHIFT(241)),
        [sym_call_expression] = ACTIONS(SHIFT(242)),
        [sym_relational_expression] = ACTIONS(SHIFT(242)),
        [sym_template_call] = ACTIONS(SHIFT(243)),
        [aux_sym_function_definition_repeat1] = ACTIONS(SHIFT(244)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(259)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(246)),
        [anon_sym_namespace] = ACTIONS(SHIFT(247)),
        [anon_sym_friend] = ACTIONS(SHIFT(7)),
        [anon_sym_typedef] = ACTIONS(SHIFT(7)),
        [anon_sym_constexpr] = ACTIONS(SHIFT(7)),
        [anon_sym_register] = ACTIONS(SHIFT(13)),
        [anon_sym_static] = ACTIONS(SHIFT(13)),
        [anon_sym_thread_local] = ACTIONS(SHIFT(13)),
        [anon_sym_extern] = ACTIONS(SHIFT(13)),
        [anon_sym_mutable] = ACTIONS(SHIFT(13)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(248)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(260)),
        [anon_sym_inline] = ACTIONS(SHIFT(14)),
        [anon_sym_virtual] = ACTIONS(SHIFT(14)),
        [anon_sym_explicit] = ACTIONS(SHIFT(14)),
        [sym_string] = ACTIONS(SHIFT(242)),
        [sym_identifier] = ACTIONS(SHIFT(250)),
        [sym_number] = ACTIONS(SHIFT(242)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_compound_statement, 2)),
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
    [250] = {
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_init_declarator] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(251)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(252)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(257)),
        [sym_identifier] = ACTIONS(SHIFT(258)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(18)),
        [sym_type_id] = ACTIONS(SHIFT(253)),
        [sym_type_specifier] = ACTIONS(SHIFT(20)),
        [sym__expression] = ACTIONS(SHIFT(254)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(23)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [anon_sym_GT] = ACTIONS(SHIFT(256)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(29)),
        [anon_sym_GT] = ACTIONS(SHIFT(255)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT] = ACTIONS(SHIFT(31)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(32)),
        [sym_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_pointer_operator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_init_declarator] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym__expression] = ACTIONS(SHIFT(33)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(34)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4), SHIFT(35)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_template_call, 4)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_template_call, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
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
    [258] = {
        [sym_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_direct_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_pointer_operator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_init_declarator] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [aux_sym_declarator_repeat1] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(251)),
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
    [259] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(261)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [260] = {
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
    [261] = {
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
    [262] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(263)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(264)),
        [sym_identifier] = ACTIONS(SHIFT(265)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [264] = {
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
    [265] = {
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(266)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(267)),
        [sym_identifier] = ACTIONS(SHIFT(268)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [267] = {
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
    [268] = {
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
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(266)),
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
    [269] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_compound_statement, 3)),
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
    [270] = {
        [sym_declarator] = ACTIONS(SHIFT(189)),
        [sym_direct_declarator] = ACTIONS(SHIFT(190)),
        [sym_pointer_operator] = ACTIONS(SHIFT(110)),
        [sym_init_declarator] = ACTIONS(SHIFT(271)),
        [aux_sym_declarator_repeat1] = ACTIONS(SHIFT(192)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(193)),
        [anon_sym_STAR] = ACTIONS(SHIFT(114)),
        [anon_sym_AMP] = ACTIONS(SHIFT(115)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [271] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(272)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(273)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(188)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [272] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(274)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [273] = {
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
    [274] = {
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
    [275] = {
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
    [276] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(44)),
        [sym__expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(46)),
        [sym_relational_expression] = ACTIONS(SHIFT(46)),
        [sym_template_call] = ACTIONS(SHIFT(47)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(291)),
        [sym_string] = ACTIONS(SHIFT(46)),
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_number] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [277] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(278)),
        [sym__expression] = ACTIONS(SHIFT(279)),
        [sym_call_expression] = ACTIONS(SHIFT(242)),
        [sym_relational_expression] = ACTIONS(SHIFT(242)),
        [sym_template_call] = ACTIONS(SHIFT(280)),
        [sym_string] = ACTIONS(SHIFT(242)),
        [sym_identifier] = ACTIONS(SHIFT(281)),
        [sym_number] = ACTIONS(SHIFT(242)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [278] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(283)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [279] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_relational_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [280] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [281] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(282)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1), SHIFT(283)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [282] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(288)),
        [sym_identifier] = ACTIONS(SHIFT(289)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [283] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(18)),
        [sym_type_id] = ACTIONS(SHIFT(284)),
        [sym_type_specifier] = ACTIONS(SHIFT(20)),
        [sym__expression] = ACTIONS(SHIFT(285)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(23)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(24)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [284] = {
        [anon_sym_GT] = ACTIONS(SHIFT(287)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [285] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(29)),
        [anon_sym_GT] = ACTIONS(SHIFT(286)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(31)),
        [anon_sym_LT] = ACTIONS(SHIFT(31)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [286] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(32)),
        [sym__expression] = ACTIONS(SHIFT(33)),
        [sym_call_expression] = ACTIONS(SHIFT(22)),
        [sym_relational_expression] = ACTIONS(SHIFT(22)),
        [sym_template_call] = ACTIONS(SHIFT(34)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_template_call, 4)),
        [sym_string] = ACTIONS(SHIFT(22)),
        [sym_identifier] = ACTIONS(SHIFT(35)),
        [sym_number] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [287] = {
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
    [288] = {
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
    [289] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_COLON_COLON] = ACTIONS(SHIFT(282)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_BANG_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_scoped_identifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [290] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(292)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(59)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(60)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(293)),
        [anon_sym_GT] = ACTIONS(SHIFT(62)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_BANG_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(62)),
        [anon_sym_LT] = ACTIONS(SHIFT(62)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [291] = {
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
    [292] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(294)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [293] = {
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
    [294] = {
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
    [295] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [296] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(297)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(298)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(188)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [297] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [298] = {
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
    [299] = {
        [sym_member_initializer] = ACTIONS(SHIFT(299)),
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 1)),
        [aux_sym_constructor_initializer_repeat1] = ACTIONS(SHIFT(307)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(302)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [300] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_constructor_initializer, 2)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(SHIFT(306)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_constructor_initializer, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [301] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_constructor_initializer, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_constructor_initializer, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [302] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(303)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [303] = {
        [anon_sym_initializer_list] = ACTIONS(SHIFT(304)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [304] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(305)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [305] = {
        [sym_member_initializer] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [aux_sym_constructor_initializer_repeat1] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_member_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [306] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_constructor_initializer, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_constructor_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [307] = {
        [sym_compound_statement] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 2)),
        [anon_sym_DOT_DOT_DOT] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(aux_sym_constructor_initializer_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [308] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [309] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_function_definition, 6)),
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
    [310] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_function_body, 2)),
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
    [311] = {
        [sym_function_body] = ACTIONS(SHIFT(315)),
        [sym_constructor_initializer] = ACTIONS(SHIFT(231)),
        [sym_compound_statement] = ACTIONS(SHIFT(232)),
        [sym_initializer] = ACTIONS(SHIFT(204)),
        [aux_sym_simple_declaration_repeat1] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(316)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_init_declarator, 1)),
        [anon_sym_COLON] = ACTIONS(SHIFT(234)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [312] = {
        [aux_sym_simple_declaration_repeat1] = ACTIONS(SHIFT(313)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(314)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(188)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [313] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(187)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [314] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_simple_declaration, 3)),
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
    [315] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_function_definition, 3)),
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
    [316] = {
        [sym_scoped_identifier] = ACTIONS(SHIFT(206)),
        [sym_initializer_clause] = ACTIONS(SHIFT(207)),
        [sym__expression] = ACTIONS(SHIFT(208)),
        [sym_call_expression] = ACTIONS(SHIFT(209)),
        [sym_relational_expression] = ACTIONS(SHIFT(209)),
        [sym_template_call] = ACTIONS(SHIFT(210)),
        [anon_sym_default] = ACTIONS(SHIFT(317)),
        [anon_sym_delete] = ACTIONS(SHIFT(317)),
        [sym_string] = ACTIONS(SHIFT(209)),
        [sym_identifier] = ACTIONS(SHIFT(211)),
        [sym_number] = ACTIONS(SHIFT(209)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [317] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(318)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [318] = {
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
        [sym_template_call] = ACTIONS(REDUCE(sym_function_definition, 5)),
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
    [319] = {
        [sym_scoped_identifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_type_specifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_template_call] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_function_definition_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [320] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_cpp);
