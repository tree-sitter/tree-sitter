#include "tree_sitter/parser.h"

#define TS_SYMBOL_COUNT 35

enum {
    ts_sym_array,
    ts_sym_assignment,
    ts_sym_block,
    ts_sym_expression,
    ts_sym_false,
    ts_sym_identifier,
    ts_sym_if,
    ts_sym_literal,
    ts_sym_null,
    ts_sym_number,
    ts_sym_object,
    ts_sym_program,
    ts_sym_statement,
    ts_sym_string,
    ts_sym_true,
    ts_sym_terminator,
    ts_aux_sym_repeat_helper1,
    ts_aux_sym_repeat_helper2,
    ts_aux_sym_repeat_helper3,
    ts_aux_sym_repeat_helper4,
    ts_aux_sym_token1,
    ts_aux_sym_token10,
    ts_aux_sym_token11,
    ts_aux_sym_token12,
    ts_aux_sym_token13,
    ts_aux_sym_token2,
    ts_aux_sym_token3,
    ts_aux_sym_token4,
    ts_aux_sym_token5,
    ts_aux_sym_token6,
    ts_aux_sym_token7,
    ts_aux_sym_token8,
    ts_aux_sym_token9,
};

SYMBOL_NAMES = {
    "array",
    "assignment",
    "block",
    "expression",
    "false",
    "identifier",
    "if",
    "literal",
    "null",
    "number",
    "object",
    "program",
    "statement",
    "string",
    "true",
    "terminator",
    "repeat_helper1",
    "repeat_helper2",
    "repeat_helper3",
    "repeat_helper4",
    "token1",
    "token10",
    "token11",
    "token12",
    "token13",
    "token2",
    "token3",
    "token4",
    "token5",
    "token6",
    "token7",
    "token8",
    "token9",
};

LEX_FN() {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if (LOOKAHEAD_CHAR() == '\n')
                ADVANCE(1);
            if (LOOKAHEAD_CHAR() == ';')
                ADVANCE(2);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 2:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 3:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(4);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(14);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'i')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(31);
            if (LOOKAHEAD_CHAR() == 'v')
                ADVANCE(35);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(38);
            LEX_ERROR();
        case 4:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(5);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(11);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(13);
            LEX_ERROR();
        case 5:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(7);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(8);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(10);
            LEX_ERROR();
        case 6:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(7);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(8);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(10);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_sym_string);
        case 8:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(9);
            if ('#' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\"')
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(8);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(10);
            LEX_ERROR();
        case 9:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(7);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(8);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_string);
        case 10:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(6);
            LEX_ERROR();
        case 11:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(12);
            if ('#' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\"')
                ADVANCE(5);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(8);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(10);
            LEX_ERROR();
        case 12:
            if (!((LOOKAHEAD_CHAR() == '\"') ||
                (LOOKAHEAD_CHAR() == '\\')))
                ADVANCE(6);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(7);
            if (LOOKAHEAD_CHAR() == '\\')
                ADVANCE(8);
            if (']' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '\\')
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym_string);
        case 13:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(5);
            LEX_ERROR();
        case 14:
            if (LOOKAHEAD_CHAR() == '.')
                ADVANCE(15);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(18);
            ACCEPT_TOKEN(ts_sym_number);
        case 15:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(17);
            ACCEPT_TOKEN(ts_sym_number);
        case 17:
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(17);
            ACCEPT_TOKEN(ts_sym_number);
        case 18:
            if (LOOKAHEAD_CHAR() == '.')
                ADVANCE(15);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(18);
            ACCEPT_TOKEN(ts_sym_number);
        case 19:
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 20:
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            if (LOOKAHEAD_CHAR() == 's')
                ADVANCE(23);
            LEX_ERROR();
        case 23:
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(24);
            LEX_ERROR();
        case 24:
            ACCEPT_TOKEN(ts_sym_false);
        case 25:
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(26);
            LEX_ERROR();
        case 26:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 27:
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(28);
            LEX_ERROR();
        case 28:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(30);
            LEX_ERROR();
        case 30:
            ACCEPT_TOKEN(ts_sym_null);
        case 31:
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(32);
            LEX_ERROR();
        case 32:
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(33);
            LEX_ERROR();
        case 33:
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(34);
            LEX_ERROR();
        case 34:
            ACCEPT_TOKEN(ts_sym_true);
        case 35:
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(36);
            LEX_ERROR();
        case 36:
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(37);
            LEX_ERROR();
        case 37:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 38:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 39:
            LEX_ERROR();
        case 40:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(41);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(42);
            LEX_ERROR();
        case 41:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 42:
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 43:
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(42);
            LEX_ERROR();
        case 44:
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(41);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(45);
            LEX_ERROR();
        case 45:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 46:
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(45);
            LEX_ERROR();
        case 47:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(4);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(14);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(42);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(31);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(38);
            LEX_ERROR();
        case 48:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(4);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(14);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(31);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(38);
            LEX_ERROR();
        case 49:
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(50);
            LEX_ERROR();
        case 50:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 51:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(4);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(45);
            LEX_ERROR();
        case 52:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(4);
            LEX_ERROR();
        case 53:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(54);
            LEX_ERROR();
        case 54:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 55:
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(4);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(14);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'i')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(31);
            if (LOOKAHEAD_CHAR() == 'v')
                ADVANCE(35);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(38);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(45);
            LEX_ERROR();
        case 56:
            if (LOOKAHEAD_CHAR() == '=')
                ADVANCE(57);
            LEX_ERROR();
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 58:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(59);
            LEX_ERROR();
        case 59:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 60:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 61:
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(38);
            LEX_ERROR();
        case 62:
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(63);
            LEX_ERROR();
        case 63:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 64:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e') ||
                ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(65);
            if ('g' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'f')
                ADVANCE(26);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 65:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 66:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't') ||
                ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(67);
            if ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'u')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 67:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'k') ||
                ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(68);
            if ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'l')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 68:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'k') ||
                ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == 'l')
                ADVANCE(69);
            if ('m' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'l')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 69:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 70:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'q') ||
                ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(71);
            if ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'r')
                ADVANCE(32);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 71:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't') ||
                ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == 'u')
                ADVANCE(72);
            if ('v' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'u')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 72:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'd') ||
                ('f' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == 'e')
                ADVANCE(73);
            if ('f' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'e')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 73:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 74:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('b' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == 'a')
                ADVANCE(75);
            if ('b' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'a')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 75:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'q') ||
                ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            if (LOOKAHEAD_CHAR() == 'r')
                ADVANCE(76);
            if ('s' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'r')
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 76:
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case ts_lex_state_error:
            if (LOOKAHEAD_CHAR() == '\n')
                ADVANCE(1);
            if (LOOKAHEAD_CHAR() == '\"')
                ADVANCE(4);
            if ((LOOKAHEAD_CHAR() == '$') ||
                ('A' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'Z') ||
                (LOOKAHEAD_CHAR() == '_') ||
                ('a' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'h') ||
                ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'm') ||
                ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 's') ||
                (LOOKAHEAD_CHAR() == 'u') ||
                ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'z'))
                ADVANCE(59);
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(63);
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(54);
            if (LOOKAHEAD_CHAR() == ',')
                ADVANCE(41);
            if ('0' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= '9')
                ADVANCE(14);
            if (LOOKAHEAD_CHAR() == ':')
                ADVANCE(50);
            if (LOOKAHEAD_CHAR() == ';')
                ADVANCE(2);
            if (LOOKAHEAD_CHAR() == '=')
                ADVANCE(57);
            if (LOOKAHEAD_CHAR() == '[')
                ADVANCE(19);
            if (LOOKAHEAD_CHAR() == ']')
                ADVANCE(42);
            if (LOOKAHEAD_CHAR() == 'f')
                ADVANCE(20);
            if (LOOKAHEAD_CHAR() == 'i')
                ADVANCE(64);
            if ('j' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'i')
                ADVANCE(25);
            if (LOOKAHEAD_CHAR() == 'n')
                ADVANCE(66);
            if ('o' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'n')
                ADVANCE(27);
            if (LOOKAHEAD_CHAR() == 't')
                ADVANCE(70);
            if ('u' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 't')
                ADVANCE(31);
            if (LOOKAHEAD_CHAR() == 'v')
                ADVANCE(74);
            if ('w' <= LOOKAHEAD_CHAR() && LOOKAHEAD_CHAR() <= 'v')
                ADVANCE(35);
            if (LOOKAHEAD_CHAR() == '{')
                ADVANCE(38);
            if (LOOKAHEAD_CHAR() == '}')
                ADVANCE(45);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

PARSE_TABLE() {
    START_TABLE(113)
    
    STATE(0);
    SET_LEX_STATE(3);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 2)
    SHIFT(ts_sym_expression, 2)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_if, 5)
    SHIFT(ts_sym_literal, 6)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_program, 7)
    SHIFT(ts_sym_statement, 8)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_aux_sym_repeat_helper1, 112)
    SHIFT(ts_aux_sym_token12, 10)
    SHIFT(ts_aux_sym_token3, 59)
    SHIFT(ts_aux_sym_token6, 80)
    SHIFT(ts_aux_sym_token8, 90)
    REDUCE(ts_builtin_sym_end, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(1);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_literal, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token2, ts_sym_literal, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(2);
    SET_LEX_STATE(0);
    SHIFT(ts_sym_terminator, 3)
    SHIFT(ts_aux_sym_token1, 4)
    SHIFT(ts_aux_sym_token2, 4)
    END_STATE();
    
    STATE(3);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_null, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_number, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_string, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_true, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token12, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token3, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token8, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_builtin_sym_end, ts_sym_statement, 2, COLLAPSE({0, 1}))
    END_STATE();
    
    STATE(4);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_null, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_number, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_string, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_true, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token12, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token3, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token6, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token8, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_builtin_sym_end, ts_sym_terminator, 1, COLLAPSE({1}))
    END_STATE();
    
    STATE(5);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_null, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_number, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_string, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_true, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token12, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token3, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token6, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token8, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_builtin_sym_end, ts_sym_statement, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(6);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_expression, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token2, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(7);
    SET_LEX_STATE(39);
    ACCEPT_INPUT(ts_builtin_sym_end)
    END_STATE();
    
    STATE(8);
    SET_LEX_STATE(3);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 2)
    SHIFT(ts_sym_expression, 2)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_if, 5)
    SHIFT(ts_sym_literal, 6)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_statement, 8)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_aux_sym_repeat_helper1, 9)
    SHIFT(ts_aux_sym_token12, 10)
    SHIFT(ts_aux_sym_token3, 59)
    SHIFT(ts_aux_sym_token6, 80)
    SHIFT(ts_aux_sym_token8, 90)
    REDUCE(ts_builtin_sym_end, ts_aux_sym_repeat_helper1, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(9);
    SET_LEX_STATE(39);
    REDUCE(ts_builtin_sym_end, ts_aux_sym_repeat_helper1, 2, COLLAPSE({0, 1}))
    END_STATE();
    
    STATE(10);
    SET_LEX_STATE(47);
    SHIFT(ts_sym_array, 11)
    SHIFT(ts_sym_expression, 12)
    SHIFT(ts_sym_false, 11)
    SHIFT(ts_sym_literal, 18)
    SHIFT(ts_sym_null, 11)
    SHIFT(ts_sym_number, 11)
    SHIFT(ts_sym_object, 11)
    SHIFT(ts_sym_string, 11)
    SHIFT(ts_sym_true, 11)
    SHIFT(ts_aux_sym_token12, 19)
    SHIFT(ts_aux_sym_token13, 58)
    SHIFT(ts_aux_sym_token6, 24)
    SHIFT(ts_builtin_sym_error, 12)
    END_STATE();
    
    STATE(11);
    SET_LEX_STATE(40);
    REDUCE(ts_aux_sym_token11, ts_sym_literal, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token13, ts_sym_literal, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(12);
    SET_LEX_STATE(40);
    SHIFT(ts_aux_sym_repeat_helper4, 13)
    SHIFT(ts_aux_sym_token11, 15)
    REDUCE(ts_aux_sym_token13, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(13);
    SET_LEX_STATE(43);
    SHIFT(ts_aux_sym_token13, 14)
    END_STATE();
    
    STATE(14);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(15);
    SET_LEX_STATE(48);
    SHIFT(ts_sym_array, 11)
    SHIFT(ts_sym_expression, 16)
    SHIFT(ts_sym_false, 11)
    SHIFT(ts_sym_literal, 18)
    SHIFT(ts_sym_null, 11)
    SHIFT(ts_sym_number, 11)
    SHIFT(ts_sym_object, 11)
    SHIFT(ts_sym_string, 11)
    SHIFT(ts_sym_true, 11)
    SHIFT(ts_aux_sym_token12, 19)
    SHIFT(ts_aux_sym_token6, 24)
    SHIFT(ts_builtin_sym_error, 16)
    END_STATE();
    
    STATE(16);
    SET_LEX_STATE(40);
    SHIFT(ts_aux_sym_repeat_helper4, 17)
    SHIFT(ts_aux_sym_token11, 15)
    REDUCE(ts_aux_sym_token13, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(17);
    SET_LEX_STATE(43);
    REDUCE(ts_aux_sym_token13, ts_aux_sym_repeat_helper4, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(18);
    SET_LEX_STATE(40);
    REDUCE(ts_aux_sym_token11, ts_sym_expression, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token13, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(19);
    SET_LEX_STATE(47);
    SHIFT(ts_sym_array, 11)
    SHIFT(ts_sym_expression, 20)
    SHIFT(ts_sym_false, 11)
    SHIFT(ts_sym_literal, 18)
    SHIFT(ts_sym_null, 11)
    SHIFT(ts_sym_number, 11)
    SHIFT(ts_sym_object, 11)
    SHIFT(ts_sym_string, 11)
    SHIFT(ts_sym_true, 11)
    SHIFT(ts_aux_sym_token12, 19)
    SHIFT(ts_aux_sym_token13, 23)
    SHIFT(ts_aux_sym_token6, 24)
    SHIFT(ts_builtin_sym_error, 20)
    END_STATE();
    
    STATE(20);
    SET_LEX_STATE(40);
    SHIFT(ts_aux_sym_repeat_helper4, 21)
    SHIFT(ts_aux_sym_token11, 15)
    REDUCE(ts_aux_sym_token13, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(21);
    SET_LEX_STATE(43);
    SHIFT(ts_aux_sym_token13, 22)
    END_STATE();
    
    STATE(22);
    SET_LEX_STATE(40);
    REDUCE(ts_aux_sym_token11, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token13, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(23);
    SET_LEX_STATE(40);
    REDUCE(ts_aux_sym_token11, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token13, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(24);
    SET_LEX_STATE(51);
    SHIFT(ts_sym_string, 25)
    SHIFT(ts_aux_sym_token7, 54)
    SHIFT(ts_builtin_sym_error, 55)
    END_STATE();
    
    STATE(25);
    SET_LEX_STATE(49);
    SHIFT(ts_aux_sym_token10, 26)
    END_STATE();
    
    STATE(26);
    SET_LEX_STATE(48);
    SHIFT(ts_sym_array, 27)
    SHIFT(ts_sym_expression, 28)
    SHIFT(ts_sym_false, 27)
    SHIFT(ts_sym_literal, 36)
    SHIFT(ts_sym_null, 27)
    SHIFT(ts_sym_number, 27)
    SHIFT(ts_sym_object, 27)
    SHIFT(ts_sym_string, 27)
    SHIFT(ts_sym_true, 27)
    SHIFT(ts_aux_sym_token12, 37)
    SHIFT(ts_aux_sym_token6, 42)
    END_STATE();
    
    STATE(27);
    SET_LEX_STATE(44);
    REDUCE(ts_aux_sym_token11, ts_sym_literal, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token7, ts_sym_literal, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(28);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 29)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(29);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 30)
    END_STATE();
    
    STATE(30);
    SET_LEX_STATE(40);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token13, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(31);
    SET_LEX_STATE(52);
    SHIFT(ts_sym_string, 32)
    SHIFT(ts_builtin_sym_error, 52)
    END_STATE();
    
    STATE(32);
    SET_LEX_STATE(49);
    SHIFT(ts_aux_sym_token10, 33)
    END_STATE();
    
    STATE(33);
    SET_LEX_STATE(48);
    SHIFT(ts_sym_array, 27)
    SHIFT(ts_sym_expression, 34)
    SHIFT(ts_sym_false, 27)
    SHIFT(ts_sym_literal, 36)
    SHIFT(ts_sym_null, 27)
    SHIFT(ts_sym_number, 27)
    SHIFT(ts_sym_object, 27)
    SHIFT(ts_sym_string, 27)
    SHIFT(ts_sym_true, 27)
    SHIFT(ts_aux_sym_token12, 37)
    SHIFT(ts_aux_sym_token6, 42)
    END_STATE();
    
    STATE(34);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 35)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(35);
    SET_LEX_STATE(46);
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 5, COLLAPSE({1, 0, 1, 0, 1}))
    END_STATE();
    
    STATE(36);
    SET_LEX_STATE(44);
    REDUCE(ts_aux_sym_token11, ts_sym_expression, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token7, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(37);
    SET_LEX_STATE(47);
    SHIFT(ts_sym_array, 11)
    SHIFT(ts_sym_expression, 38)
    SHIFT(ts_sym_false, 11)
    SHIFT(ts_sym_literal, 18)
    SHIFT(ts_sym_null, 11)
    SHIFT(ts_sym_number, 11)
    SHIFT(ts_sym_object, 11)
    SHIFT(ts_sym_string, 11)
    SHIFT(ts_sym_true, 11)
    SHIFT(ts_aux_sym_token12, 19)
    SHIFT(ts_aux_sym_token13, 41)
    SHIFT(ts_aux_sym_token6, 24)
    SHIFT(ts_builtin_sym_error, 38)
    END_STATE();
    
    STATE(38);
    SET_LEX_STATE(40);
    SHIFT(ts_aux_sym_repeat_helper4, 39)
    SHIFT(ts_aux_sym_token11, 15)
    REDUCE(ts_aux_sym_token13, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(39);
    SET_LEX_STATE(43);
    SHIFT(ts_aux_sym_token13, 40)
    END_STATE();
    
    STATE(40);
    SET_LEX_STATE(44);
    REDUCE(ts_aux_sym_token11, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token7, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(41);
    SET_LEX_STATE(44);
    REDUCE(ts_aux_sym_token11, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token7, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(42);
    SET_LEX_STATE(51);
    SHIFT(ts_sym_string, 43)
    SHIFT(ts_aux_sym_token7, 48)
    SHIFT(ts_builtin_sym_error, 49)
    END_STATE();
    
    STATE(43);
    SET_LEX_STATE(49);
    SHIFT(ts_aux_sym_token10, 44)
    END_STATE();
    
    STATE(44);
    SET_LEX_STATE(48);
    SHIFT(ts_sym_array, 27)
    SHIFT(ts_sym_expression, 45)
    SHIFT(ts_sym_false, 27)
    SHIFT(ts_sym_literal, 36)
    SHIFT(ts_sym_null, 27)
    SHIFT(ts_sym_number, 27)
    SHIFT(ts_sym_object, 27)
    SHIFT(ts_sym_string, 27)
    SHIFT(ts_sym_true, 27)
    SHIFT(ts_aux_sym_token12, 37)
    SHIFT(ts_aux_sym_token6, 42)
    END_STATE();
    
    STATE(45);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 46)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(46);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 47)
    END_STATE();
    
    STATE(47);
    SET_LEX_STATE(44);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token7, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(48);
    SET_LEX_STATE(44);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token7, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(49);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 50)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(50);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 51)
    END_STATE();
    
    STATE(51);
    SET_LEX_STATE(44);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token7, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(52);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 53)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(53);
    SET_LEX_STATE(46);
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 3, COLLAPSE({1, 0, 1}))
    END_STATE();
    
    STATE(54);
    SET_LEX_STATE(40);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token13, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(55);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 56)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(56);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 57)
    END_STATE();
    
    STATE(57);
    SET_LEX_STATE(40);
    REDUCE(ts_aux_sym_token11, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token13, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(58);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_array, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(59);
    SET_LEX_STATE(62);
    SHIFT(ts_aux_sym_token4, 60)
    END_STATE();
    
    STATE(60);
    SET_LEX_STATE(48);
    SHIFT(ts_sym_array, 61)
    SHIFT(ts_sym_expression, 62)
    SHIFT(ts_sym_false, 61)
    SHIFT(ts_sym_literal, 94)
    SHIFT(ts_sym_null, 61)
    SHIFT(ts_sym_number, 61)
    SHIFT(ts_sym_object, 61)
    SHIFT(ts_sym_string, 61)
    SHIFT(ts_sym_true, 61)
    SHIFT(ts_aux_sym_token12, 95)
    SHIFT(ts_aux_sym_token6, 100)
    END_STATE();
    
    STATE(61);
    SET_LEX_STATE(53);
    REDUCE(ts_aux_sym_token5, ts_sym_literal, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(62);
    SET_LEX_STATE(53);
    SHIFT(ts_aux_sym_token5, 63)
    END_STATE();
    
    STATE(63);
    SET_LEX_STATE(61);
    SHIFT(ts_sym_block, 64)
    SHIFT(ts_aux_sym_token6, 65)
    END_STATE();
    
    STATE(64);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_null, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_number, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_string, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_true, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token12, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token3, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token6, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token8, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_builtin_sym_end, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    END_STATE();
    
    STATE(65);
    SET_LEX_STATE(55);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 66)
    SHIFT(ts_sym_expression, 66)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_if, 69)
    SHIFT(ts_sym_literal, 6)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_statement, 70)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_aux_sym_repeat_helper2, 110)
    SHIFT(ts_aux_sym_token12, 10)
    SHIFT(ts_aux_sym_token3, 72)
    SHIFT(ts_aux_sym_token6, 80)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token8, 90)
    END_STATE();
    
    STATE(66);
    SET_LEX_STATE(0);
    SHIFT(ts_sym_terminator, 67)
    SHIFT(ts_aux_sym_token1, 68)
    SHIFT(ts_aux_sym_token2, 68)
    END_STATE();
    
    STATE(67);
    SET_LEX_STATE(55);
    REDUCE(ts_sym_false, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_null, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_number, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_string, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_sym_true, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token12, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token3, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token7, ts_sym_statement, 2, COLLAPSE({0, 1}))
    REDUCE(ts_aux_sym_token8, ts_sym_statement, 2, COLLAPSE({0, 1}))
    END_STATE();
    
    STATE(68);
    SET_LEX_STATE(55);
    REDUCE(ts_sym_false, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_null, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_number, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_string, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_sym_true, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token12, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token3, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token6, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token7, ts_sym_terminator, 1, COLLAPSE({1}))
    REDUCE(ts_aux_sym_token8, ts_sym_terminator, 1, COLLAPSE({1}))
    END_STATE();
    
    STATE(69);
    SET_LEX_STATE(55);
    REDUCE(ts_sym_false, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_null, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_number, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_string, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_sym_true, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token12, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token3, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token6, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token7, ts_sym_statement, 1, COLLAPSE({0}))
    REDUCE(ts_aux_sym_token8, ts_sym_statement, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(70);
    SET_LEX_STATE(55);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 66)
    SHIFT(ts_sym_expression, 66)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_if, 69)
    SHIFT(ts_sym_literal, 6)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_statement, 70)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_aux_sym_repeat_helper2, 71)
    SHIFT(ts_aux_sym_token12, 10)
    SHIFT(ts_aux_sym_token3, 72)
    SHIFT(ts_aux_sym_token6, 80)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token8, 90)
    END_STATE();
    
    STATE(71);
    SET_LEX_STATE(46);
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper2, 2, COLLAPSE({0, 1}))
    END_STATE();
    
    STATE(72);
    SET_LEX_STATE(62);
    SHIFT(ts_aux_sym_token4, 73)
    END_STATE();
    
    STATE(73);
    SET_LEX_STATE(48);
    SHIFT(ts_sym_array, 61)
    SHIFT(ts_sym_expression, 74)
    SHIFT(ts_sym_false, 61)
    SHIFT(ts_sym_literal, 94)
    SHIFT(ts_sym_null, 61)
    SHIFT(ts_sym_number, 61)
    SHIFT(ts_sym_object, 61)
    SHIFT(ts_sym_string, 61)
    SHIFT(ts_sym_true, 61)
    SHIFT(ts_aux_sym_token12, 95)
    SHIFT(ts_aux_sym_token6, 100)
    END_STATE();
    
    STATE(74);
    SET_LEX_STATE(53);
    SHIFT(ts_aux_sym_token5, 75)
    END_STATE();
    
    STATE(75);
    SET_LEX_STATE(61);
    SHIFT(ts_sym_block, 76)
    SHIFT(ts_aux_sym_token6, 77)
    END_STATE();
    
    STATE(76);
    SET_LEX_STATE(55);
    REDUCE(ts_sym_false, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_null, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_number, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_string, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_sym_true, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token12, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token3, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token6, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token7, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token8, ts_sym_if, 5, COLLAPSE({1, 1, 0, 1, 0}))
    END_STATE();
    
    STATE(77);
    SET_LEX_STATE(55);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_assignment, 66)
    SHIFT(ts_sym_expression, 66)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_if, 69)
    SHIFT(ts_sym_literal, 6)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_statement, 70)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_aux_sym_repeat_helper2, 78)
    SHIFT(ts_aux_sym_token12, 10)
    SHIFT(ts_aux_sym_token3, 72)
    SHIFT(ts_aux_sym_token6, 80)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper2, 0, COLLAPSE({}))
    SHIFT(ts_aux_sym_token8, 90)
    END_STATE();
    
    STATE(78);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 79)
    END_STATE();
    
    STATE(79);
    SET_LEX_STATE(55);
    REDUCE(ts_sym_false, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_null, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_number, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_string, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_true, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token12, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token3, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token7, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token8, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    END_STATE();
    
    STATE(80);
    SET_LEX_STATE(51);
    SHIFT(ts_sym_string, 81)
    SHIFT(ts_aux_sym_token7, 86)
    SHIFT(ts_builtin_sym_error, 87)
    END_STATE();
    
    STATE(81);
    SET_LEX_STATE(49);
    SHIFT(ts_aux_sym_token10, 82)
    END_STATE();
    
    STATE(82);
    SET_LEX_STATE(48);
    SHIFT(ts_sym_array, 27)
    SHIFT(ts_sym_expression, 83)
    SHIFT(ts_sym_false, 27)
    SHIFT(ts_sym_literal, 36)
    SHIFT(ts_sym_null, 27)
    SHIFT(ts_sym_number, 27)
    SHIFT(ts_sym_object, 27)
    SHIFT(ts_sym_string, 27)
    SHIFT(ts_sym_true, 27)
    SHIFT(ts_aux_sym_token12, 37)
    SHIFT(ts_aux_sym_token6, 42)
    END_STATE();
    
    STATE(83);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 84)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(84);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 85)
    END_STATE();
    
    STATE(85);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(86);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_object, 2, COLLAPSE({1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(87);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 88)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(88);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 89)
    END_STATE();
    
    STATE(89);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    REDUCE(ts_aux_sym_token2, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(90);
    SET_LEX_STATE(58);
    SHIFT(ts_sym_identifier, 91)
    END_STATE();
    
    STATE(91);
    SET_LEX_STATE(56);
    SHIFT(ts_aux_sym_token9, 92)
    END_STATE();
    
    STATE(92);
    SET_LEX_STATE(48);
    SHIFT(ts_sym_array, 1)
    SHIFT(ts_sym_expression, 93)
    SHIFT(ts_sym_false, 1)
    SHIFT(ts_sym_literal, 6)
    SHIFT(ts_sym_null, 1)
    SHIFT(ts_sym_number, 1)
    SHIFT(ts_sym_object, 1)
    SHIFT(ts_sym_string, 1)
    SHIFT(ts_sym_true, 1)
    SHIFT(ts_aux_sym_token12, 10)
    SHIFT(ts_aux_sym_token6, 80)
    END_STATE();
    
    STATE(93);
    SET_LEX_STATE(0);
    REDUCE(ts_aux_sym_token1, ts_sym_assignment, 4, COLLAPSE({1, 0, 1, 0}))
    REDUCE(ts_aux_sym_token2, ts_sym_assignment, 4, COLLAPSE({1, 0, 1, 0}))
    END_STATE();
    
    STATE(94);
    SET_LEX_STATE(53);
    REDUCE(ts_aux_sym_token5, ts_sym_expression, 1, COLLAPSE({0}))
    END_STATE();
    
    STATE(95);
    SET_LEX_STATE(47);
    SHIFT(ts_sym_array, 11)
    SHIFT(ts_sym_expression, 96)
    SHIFT(ts_sym_false, 11)
    SHIFT(ts_sym_literal, 18)
    SHIFT(ts_sym_null, 11)
    SHIFT(ts_sym_number, 11)
    SHIFT(ts_sym_object, 11)
    SHIFT(ts_sym_string, 11)
    SHIFT(ts_sym_true, 11)
    SHIFT(ts_aux_sym_token12, 19)
    SHIFT(ts_aux_sym_token13, 99)
    SHIFT(ts_aux_sym_token6, 24)
    SHIFT(ts_builtin_sym_error, 96)
    END_STATE();
    
    STATE(96);
    SET_LEX_STATE(40);
    SHIFT(ts_aux_sym_repeat_helper4, 97)
    SHIFT(ts_aux_sym_token11, 15)
    REDUCE(ts_aux_sym_token13, ts_aux_sym_repeat_helper4, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(97);
    SET_LEX_STATE(43);
    SHIFT(ts_aux_sym_token13, 98)
    END_STATE();
    
    STATE(98);
    SET_LEX_STATE(53);
    REDUCE(ts_aux_sym_token5, ts_sym_array, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(99);
    SET_LEX_STATE(53);
    REDUCE(ts_aux_sym_token5, ts_sym_array, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(100);
    SET_LEX_STATE(51);
    SHIFT(ts_sym_string, 101)
    SHIFT(ts_aux_sym_token7, 106)
    SHIFT(ts_builtin_sym_error, 107)
    END_STATE();
    
    STATE(101);
    SET_LEX_STATE(49);
    SHIFT(ts_aux_sym_token10, 102)
    END_STATE();
    
    STATE(102);
    SET_LEX_STATE(48);
    SHIFT(ts_sym_array, 27)
    SHIFT(ts_sym_expression, 103)
    SHIFT(ts_sym_false, 27)
    SHIFT(ts_sym_literal, 36)
    SHIFT(ts_sym_null, 27)
    SHIFT(ts_sym_number, 27)
    SHIFT(ts_sym_object, 27)
    SHIFT(ts_sym_string, 27)
    SHIFT(ts_sym_true, 27)
    SHIFT(ts_aux_sym_token12, 37)
    SHIFT(ts_aux_sym_token6, 42)
    END_STATE();
    
    STATE(103);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 104)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(104);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 105)
    END_STATE();
    
    STATE(105);
    SET_LEX_STATE(53);
    REDUCE(ts_aux_sym_token5, ts_sym_object, 6, COLLAPSE({1, 0, 1, 0, 1, 1}))
    END_STATE();
    
    STATE(106);
    SET_LEX_STATE(53);
    REDUCE(ts_aux_sym_token5, ts_sym_object, 2, COLLAPSE({1, 1}))
    END_STATE();
    
    STATE(107);
    SET_LEX_STATE(44);
    SHIFT(ts_aux_sym_repeat_helper3, 108)
    SHIFT(ts_aux_sym_token11, 31)
    REDUCE(ts_aux_sym_token7, ts_aux_sym_repeat_helper3, 0, COLLAPSE({}))
    END_STATE();
    
    STATE(108);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 109)
    END_STATE();
    
    STATE(109);
    SET_LEX_STATE(53);
    REDUCE(ts_aux_sym_token5, ts_sym_object, 4, COLLAPSE({1, 0, 1, 1}))
    END_STATE();
    
    STATE(110);
    SET_LEX_STATE(46);
    SHIFT(ts_aux_sym_token7, 111)
    END_STATE();
    
    STATE(111);
    SET_LEX_STATE(3);
    REDUCE(ts_sym_false, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_null, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_number, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_string, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_sym_true, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token12, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token3, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token6, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_aux_sym_token8, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    REDUCE(ts_builtin_sym_end, ts_sym_block, 3, COLLAPSE({1, 1, 1}))
    END_STATE();
    
    STATE(112);
    SET_LEX_STATE(39);
    REDUCE(ts_builtin_sym_end, ts_sym_program, 1, COLLAPSE({1}))
    END_STATE();
    
    END_TABLE();
}

EXPORT_PARSER(ts_parser_javascript);
