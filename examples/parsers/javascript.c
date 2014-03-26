#include "tree_sitter/parser.h"

#define TS_SYMBOL_COUNT 35

enum {
    ts_sym__IF = 2,
    ts_sym__VAR = 3,
    ts_sym__terminator = 4,
    ts_sym_array = 5,
    ts_sym_assignment = 6,
    ts_sym_expression = 7,
    ts_sym_false = 8,
    ts_sym_identifier = 9,
    ts_sym_if_statement = 10,
    ts_sym_literal = 11,
    ts_sym_null = 12,
    ts_sym_number = 13,
    ts_sym_object = 14,
    ts_sym_program = 15,
    ts_sym_statement = 16,
    ts_sym_statement_block = 17,
    ts_sym_string = 18,
    ts_sym_true = 19,
    ts_aux_sym_repeat_helper1 = 20,
    ts_aux_sym_repeat_helper2 = 21,
    ts_aux_sym_repeat_helper3 = 22,
    ts_aux_sym_repeat_helper4 = 23,
    ts_aux_sym_token1 = 24,
    ts_aux_sym_token10 = 25,
    ts_aux_sym_token11 = 26,
    ts_aux_sym_token2 = 27,
    ts_aux_sym_token3 = 28,
    ts_aux_sym_token4 = 29,
    ts_aux_sym_token5 = 30,
    ts_aux_sym_token6 = 31,
    ts_aux_sym_token7 = 32,
    ts_aux_sym_token8 = 33,
    ts_aux_sym_token9 = 34,
};

SYMBOL_NAMES = {
    "error",
    "end",
    "_IF",
    "_VAR",
    "_terminator",
    "array",
    "assignment",
    "expression",
    "false",
    "identifier",
    "if_statement",
    "literal",
    "null",
    "number",
    "object",
    "program",
    "statement",
    "statement_block",
    "string",
    "true",
    "repeat_helper1",
    "repeat_helper2",
    "repeat_helper3",
    "repeat_helper4",
    "token1",
    "token10",
    "token11",
    "token2",
    "token3",
    "token4",
    "token5",
    "token6",
    "token7",
    "token8",
    "token9",
};

HIDDEN_SYMBOLS(35) = {    
    [ts_sym__IF] = 1,    
    [ts_sym__VAR] = 1,    
    [ts_sym__terminator] = 1,    
    [ts_aux_sym_repeat_helper1] = 1,    
    [ts_aux_sym_repeat_helper2] = 1,    
    [ts_aux_sym_repeat_helper3] = 1,    
    [ts_aux_sym_repeat_helper4] = 1,    
    [ts_aux_sym_token1] = 1,    
    [ts_aux_sym_token10] = 1,    
    [ts_aux_sym_token11] = 1,    
    [ts_aux_sym_token2] = 1,    
    [ts_aux_sym_token3] = 1,    
    [ts_aux_sym_token4] = 1,    
    [ts_aux_sym_token5] = 1,    
    [ts_aux_sym_token6] = 1,    
    [ts_aux_sym_token7] = 1,    
    [ts_aux_sym_token8] = 1,    
    [ts_aux_sym_token9] = 1,
};

LEX_FN() {
    START_LEXER();
    switch (lex_state) {
        case 0:
            if (lookahead == ')')
                ADVANCE(1);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 2:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 3:
            if (lookahead == 'a')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (lookahead == 'l')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (lookahead == 's')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (lookahead == 'e')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_sym_false);
        case 8:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(9);
            if (lookahead == '\\')
                ADVANCE(15);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(17);
            LEX_ERROR();
        case 9:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 10:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_sym_string);
        case 12:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(13);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(10);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 13:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_string);
        case 14:
            if (lookahead == '\"')
                ADVANCE(10);
            LEX_ERROR();
        case 15:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(16);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(9);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            LEX_ERROR();
        case 16:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(10);
            if (lookahead == '\"')
                ADVANCE(11);
            if (lookahead == '\\')
                ADVANCE(12);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym_string);
        case 17:
            if (lookahead == '\"')
                ADVANCE(9);
            LEX_ERROR();
        case 18:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 19:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 20:
            if (lookahead == '.')
                ADVANCE(21);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_number);
        case 21:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 23:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 24:
            if (lookahead == '.')
                ADVANCE(21);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_number);
        case 25:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 26:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'a')
                ADVANCE(27);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 27:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 's')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'e')
                ADVANCE(30);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 30:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'f')
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 32:
            ACCEPT_TOKEN(ts_sym__IF);
        case 33:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__IF);
        case 34:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'u')
                ADVANCE(35);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 35:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(36);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 36:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'l')
                ADVANCE(37);
            if ('m' <= lookahead && lookahead <= 'l')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            ACCEPT_TOKEN(ts_sym_null);
        case 39:
            if (lookahead == 'l')
                ADVANCE(38);
            LEX_ERROR();
        case 40:
            if (lookahead == 'l')
                ADVANCE(39);
            LEX_ERROR();
        case 41:
            if (lookahead == 'u')
                ADVANCE(40);
            LEX_ERROR();
        case 42:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'r')
                ADVANCE(43);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 43:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'u')
                ADVANCE(44);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'e')
                ADVANCE(45);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            ACCEPT_TOKEN(ts_sym_true);
        case 47:
            if (lookahead == 'e')
                ADVANCE(46);
            LEX_ERROR();
        case 48:
            if (lookahead == 'u')
                ADVANCE(47);
            LEX_ERROR();
        case 49:
            if (lookahead == 'r')
                ADVANCE(48);
            LEX_ERROR();
        case 50:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'a')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if (lookahead == 'r')
                ADVANCE(52);
            LEX_ERROR();
        case 52:
            ACCEPT_TOKEN(ts_sym__VAR);
        case 53:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == 'r')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 54:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            ACCEPT_TOKEN(ts_sym__VAR);
        case 55:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 56:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(55);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 58:
            if (lookahead == '\n')
                ADVANCE(59);
            if (lookahead == ';')
                ADVANCE(60);
            LEX_ERROR();
        case 59:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 60:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 61:
            if (lookahead == ',')
                ADVANCE(62);
            if (lookahead == ']')
                ADVANCE(63);
            LEX_ERROR();
        case 62:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 63:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 64:
            if (lookahead == ']')
                ADVANCE(63);
            LEX_ERROR();
        case 65:
            if (lookahead == ',')
                ADVANCE(62);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 66:
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 67:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == ']')
                ADVANCE(63);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 68:
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 69:
            if (lookahead == ':')
                ADVANCE(70);
            LEX_ERROR();
        case 70:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 71:
            if (lookahead == '\"')
                ADVANCE(8);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 72:
            if (lookahead == '\"')
                ADVANCE(8);
            LEX_ERROR();
        case 73:
            if (lookahead == '=')
                ADVANCE(74);
            LEX_ERROR();
        case 74:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 75:
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            LEX_ERROR();
        case 76:
            if (lookahead == '{')
                ADVANCE(55);
            LEX_ERROR();
        case 77:
            if (lookahead == '(')
                ADVANCE(78);
            LEX_ERROR();
        case 78:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 79:
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '\n')
                ADVANCE(59);
            if (lookahead == '\"')
                ADVANCE(8);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 's') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(18);
            if (lookahead == '(')
                ADVANCE(78);
            if (lookahead == ')')
                ADVANCE(1);
            if (lookahead == ',')
                ADVANCE(62);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(20);
            if (lookahead == ':')
                ADVANCE(70);
            if (lookahead == ';')
                ADVANCE(60);
            if (lookahead == '=')
                ADVANCE(74);
            if (lookahead == '[')
                ADVANCE(25);
            if (lookahead == ']')
                ADVANCE(63);
            if (lookahead == 'f')
                ADVANCE(26);
            if (lookahead == 'i')
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(34);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(41);
            if (lookahead == 't')
                ADVANCE(42);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(49);
            if (lookahead == 'v')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(55);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES(113) = {
    [0] = 2,
    [1] = 77,
    [2] = 68,
    [3] = 0,
    [4] = 0,
    [5] = 76,
    [6] = 2,
    [7] = 56,
    [8] = 77,
    [9] = 68,
    [10] = 0,
    [11] = 76,
    [12] = 56,
    [13] = 56,
    [14] = 75,
    [15] = 73,
    [16] = 68,
    [17] = 58,
    [18] = 58,
    [19] = 58,
    [20] = 67,
    [21] = 61,
    [22] = 61,
    [23] = 64,
    [24] = 58,
    [25] = 68,
    [26] = 61,
    [27] = 64,
    [28] = 61,
    [29] = 67,
    [30] = 61,
    [31] = 64,
    [32] = 61,
    [33] = 61,
    [34] = 71,
    [35] = 69,
    [36] = 68,
    [37] = 65,
    [38] = 65,
    [39] = 66,
    [40] = 61,
    [41] = 72,
    [42] = 69,
    [43] = 68,
    [44] = 65,
    [45] = 66,
    [46] = 65,
    [47] = 67,
    [48] = 61,
    [49] = 64,
    [50] = 65,
    [51] = 65,
    [52] = 71,
    [53] = 69,
    [54] = 68,
    [55] = 65,
    [56] = 66,
    [57] = 65,
    [58] = 65,
    [59] = 65,
    [60] = 66,
    [61] = 65,
    [62] = 65,
    [63] = 66,
    [64] = 61,
    [65] = 65,
    [66] = 66,
    [67] = 61,
    [68] = 58,
    [69] = 71,
    [70] = 69,
    [71] = 68,
    [72] = 65,
    [73] = 66,
    [74] = 58,
    [75] = 58,
    [76] = 65,
    [77] = 66,
    [78] = 58,
    [79] = 58,
    [80] = 56,
    [81] = 56,
    [82] = 56,
    [83] = 56,
    [84] = 66,
    [85] = 66,
    [86] = 56,
    [87] = 0,
    [88] = 67,
    [89] = 61,
    [90] = 64,
    [91] = 0,
    [92] = 0,
    [93] = 71,
    [94] = 69,
    [95] = 68,
    [96] = 65,
    [97] = 66,
    [98] = 0,
    [99] = 0,
    [100] = 65,
    [101] = 66,
    [102] = 0,
    [103] = 66,
    [104] = 2,
    [105] = 58,
    [106] = 2,
    [107] = 2,
    [108] = 2,
    [109] = 79,
    [110] = 2,
    [111] = 79,
    [112] = 79,
};

PARSE_TABLE(113, 35) = {
    [0] = {    
        [ts_sym__IF] = SHIFT(1),    
        [ts_sym__VAR] = SHIFT(14),    
        [ts_sym_array] = SHIFT(17),    
        [ts_sym_assignment] = SHIFT(105),    
        [ts_sym_expression] = SHIFT(105),    
        [ts_sym_false] = SHIFT(17),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(108),    
        [ts_sym_literal] = SHIFT(19),    
        [ts_sym_null] = SHIFT(17),    
        [ts_sym_number] = SHIFT(17),    
        [ts_sym_object] = SHIFT(17),    
        [ts_sym_program] = SHIFT(109),    
        [ts_sym_statement] = SHIFT(110),    
        [ts_sym_string] = SHIFT(17),    
        [ts_sym_true] = SHIFT(17),    
        [ts_aux_sym_repeat_helper1] = SHIFT(112),    
        [ts_aux_sym_token10] = SHIFT(20),    
        [ts_aux_sym_token5] = SHIFT(69),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [1] = {    
        [ts_aux_sym_token3] = SHIFT(2),
    },
    
    [2] = {    
        [ts_sym_array] = SHIFT(3),    
        [ts_sym_expression] = SHIFT(4),    
        [ts_sym_false] = SHIFT(3),    
        [ts_sym_identifier] = SHIFT(87),    
        [ts_sym_literal] = SHIFT(87),    
        [ts_sym_null] = SHIFT(3),    
        [ts_sym_number] = SHIFT(3),    
        [ts_sym_object] = SHIFT(3),    
        [ts_sym_string] = SHIFT(3),    
        [ts_sym_true] = SHIFT(3),    
        [ts_aux_sym_token10] = SHIFT(88),    
        [ts_aux_sym_token5] = SHIFT(93),
    },
    
    [3] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_literal, 1),
    },
    
    [4] = {    
        [ts_aux_sym_token4] = SHIFT(5),
    },
    
    [5] = {    
        [ts_sym_statement_block] = SHIFT(6),    
        [ts_aux_sym_token5] = SHIFT(7),
    },
    
    [6] = {    
        [ts_sym__IF] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__VAR] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_if_statement, 5),
    },
    
    [7] = {    
        [ts_sym__IF] = SHIFT(8),    
        [ts_sym__VAR] = SHIFT(14),    
        [ts_sym_array] = SHIFT(17),    
        [ts_sym_assignment] = SHIFT(79),    
        [ts_sym_expression] = SHIFT(79),    
        [ts_sym_false] = SHIFT(17),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(82),    
        [ts_sym_literal] = SHIFT(19),    
        [ts_sym_null] = SHIFT(17),    
        [ts_sym_number] = SHIFT(17),    
        [ts_sym_object] = SHIFT(17),    
        [ts_sym_statement] = SHIFT(83),    
        [ts_sym_string] = SHIFT(17),    
        [ts_sym_true] = SHIFT(17),    
        [ts_aux_sym_repeat_helper2] = SHIFT(103),    
        [ts_aux_sym_token10] = SHIFT(20),    
        [ts_aux_sym_token5] = SHIFT(69),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [8] = {    
        [ts_aux_sym_token3] = SHIFT(9),
    },
    
    [9] = {    
        [ts_sym_array] = SHIFT(3),    
        [ts_sym_expression] = SHIFT(10),    
        [ts_sym_false] = SHIFT(3),    
        [ts_sym_identifier] = SHIFT(87),    
        [ts_sym_literal] = SHIFT(87),    
        [ts_sym_null] = SHIFT(3),    
        [ts_sym_number] = SHIFT(3),    
        [ts_sym_object] = SHIFT(3),    
        [ts_sym_string] = SHIFT(3),    
        [ts_sym_true] = SHIFT(3),    
        [ts_aux_sym_token10] = SHIFT(88),    
        [ts_aux_sym_token5] = SHIFT(93),
    },
    
    [10] = {    
        [ts_aux_sym_token4] = SHIFT(11),
    },
    
    [11] = {    
        [ts_sym_statement_block] = SHIFT(12),    
        [ts_aux_sym_token5] = SHIFT(13),
    },
    
    [12] = {    
        [ts_sym__IF] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym__VAR] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),    
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_if_statement, 5),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_if_statement, 5),
    },
    
    [13] = {    
        [ts_sym__IF] = SHIFT(8),    
        [ts_sym__VAR] = SHIFT(14),    
        [ts_sym_array] = SHIFT(17),    
        [ts_sym_assignment] = SHIFT(79),    
        [ts_sym_expression] = SHIFT(79),    
        [ts_sym_false] = SHIFT(17),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(82),    
        [ts_sym_literal] = SHIFT(19),    
        [ts_sym_null] = SHIFT(17),    
        [ts_sym_number] = SHIFT(17),    
        [ts_sym_object] = SHIFT(17),    
        [ts_sym_statement] = SHIFT(83),    
        [ts_sym_string] = SHIFT(17),    
        [ts_sym_true] = SHIFT(17),    
        [ts_aux_sym_repeat_helper2] = SHIFT(85),    
        [ts_aux_sym_token10] = SHIFT(20),    
        [ts_aux_sym_token5] = SHIFT(69),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [14] = {    
        [ts_sym_identifier] = SHIFT(15),
    },
    
    [15] = {    
        [ts_aux_sym_token7] = SHIFT(16),
    },
    
    [16] = {    
        [ts_sym_array] = SHIFT(17),    
        [ts_sym_expression] = SHIFT(18),    
        [ts_sym_false] = SHIFT(17),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_literal] = SHIFT(19),    
        [ts_sym_null] = SHIFT(17),    
        [ts_sym_number] = SHIFT(17),    
        [ts_sym_object] = SHIFT(17),    
        [ts_sym_string] = SHIFT(17),    
        [ts_sym_true] = SHIFT(17),    
        [ts_aux_sym_token10] = SHIFT(20),    
        [ts_aux_sym_token5] = SHIFT(69),
    },
    
    [17] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_literal, 1),
    },
    
    [18] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_assignment, 4),
    },
    
    [19] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
    },
    
    [20] = {    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(22),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(28),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_token10] = SHIFT(29),    
        [ts_aux_sym_token11] = SHIFT(68),    
        [ts_aux_sym_token5] = SHIFT(34),    
        [ts_builtin_sym_error] = SHIFT(22),
    },
    
    [21] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    
    [22] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(23),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(25),
    },
    
    [23] = {    
        [ts_aux_sym_token11] = SHIFT(24),
    },
    
    [24] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 4),
    },
    
    [25] = {    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(26),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(28),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_token10] = SHIFT(29),    
        [ts_aux_sym_token5] = SHIFT(34),    
        [ts_builtin_sym_error] = SHIFT(26),
    },
    
    [26] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(27),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(25),
    },
    
    [27] = {    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 3),
    },
    
    [28] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    
    [29] = {    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(30),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(28),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_token10] = SHIFT(29),    
        [ts_aux_sym_token11] = SHIFT(33),    
        [ts_aux_sym_token5] = SHIFT(34),    
        [ts_builtin_sym_error] = SHIFT(30),
    },
    
    [30] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(31),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(25),
    },
    
    [31] = {    
        [ts_aux_sym_token11] = SHIFT(32),
    },
    
    [32] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    
    [33] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    
    [34] = {    
        [ts_sym_string] = SHIFT(35),    
        [ts_aux_sym_token6] = SHIFT(64),    
        [ts_builtin_sym_error] = SHIFT(65),
    },
    
    [35] = {    
        [ts_aux_sym_token8] = SHIFT(36),
    },
    
    [36] = {    
        [ts_sym_array] = SHIFT(37),    
        [ts_sym_expression] = SHIFT(38),    
        [ts_sym_false] = SHIFT(37),    
        [ts_sym_identifier] = SHIFT(46),    
        [ts_sym_literal] = SHIFT(46),    
        [ts_sym_null] = SHIFT(37),    
        [ts_sym_number] = SHIFT(37),    
        [ts_sym_object] = SHIFT(37),    
        [ts_sym_string] = SHIFT(37),    
        [ts_sym_true] = SHIFT(37),    
        [ts_aux_sym_token10] = SHIFT(47),    
        [ts_aux_sym_token5] = SHIFT(52),
    },
    
    [37] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_literal, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_literal, 1),
    },
    
    [38] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(39),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [39] = {    
        [ts_aux_sym_token6] = SHIFT(40),
    },
    
    [40] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    
    [41] = {    
        [ts_sym_string] = SHIFT(42),    
        [ts_builtin_sym_error] = SHIFT(62),
    },
    
    [42] = {    
        [ts_aux_sym_token8] = SHIFT(43),
    },
    
    [43] = {    
        [ts_sym_array] = SHIFT(37),    
        [ts_sym_expression] = SHIFT(44),    
        [ts_sym_false] = SHIFT(37),    
        [ts_sym_identifier] = SHIFT(46),    
        [ts_sym_literal] = SHIFT(46),    
        [ts_sym_null] = SHIFT(37),    
        [ts_sym_number] = SHIFT(37),    
        [ts_sym_object] = SHIFT(37),    
        [ts_sym_string] = SHIFT(37),    
        [ts_sym_true] = SHIFT(37),    
        [ts_aux_sym_token10] = SHIFT(47),    
        [ts_aux_sym_token5] = SHIFT(52),
    },
    
    [44] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(45),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [45] = {    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 5),
    },
    
    [46] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_expression, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
    },
    
    [47] = {    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(48),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(28),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_token10] = SHIFT(29),    
        [ts_aux_sym_token11] = SHIFT(51),    
        [ts_aux_sym_token5] = SHIFT(34),    
        [ts_builtin_sym_error] = SHIFT(48),
    },
    
    [48] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(49),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(25),
    },
    
    [49] = {    
        [ts_aux_sym_token11] = SHIFT(50),
    },
    
    [50] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 4),
    },
    
    [51] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_array, 2),
    },
    
    [52] = {    
        [ts_sym_string] = SHIFT(53),    
        [ts_aux_sym_token6] = SHIFT(58),    
        [ts_builtin_sym_error] = SHIFT(59),
    },
    
    [53] = {    
        [ts_aux_sym_token8] = SHIFT(54),
    },
    
    [54] = {    
        [ts_sym_array] = SHIFT(37),    
        [ts_sym_expression] = SHIFT(55),    
        [ts_sym_false] = SHIFT(37),    
        [ts_sym_identifier] = SHIFT(46),    
        [ts_sym_literal] = SHIFT(46),    
        [ts_sym_null] = SHIFT(37),    
        [ts_sym_number] = SHIFT(37),    
        [ts_sym_object] = SHIFT(37),    
        [ts_sym_string] = SHIFT(37),    
        [ts_sym_true] = SHIFT(37),    
        [ts_aux_sym_token10] = SHIFT(47),    
        [ts_aux_sym_token5] = SHIFT(52),
    },
    
    [55] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(56),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [56] = {    
        [ts_aux_sym_token6] = SHIFT(57),
    },
    
    [57] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 6),
    },
    
    [58] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    
    [59] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(60),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [60] = {    
        [ts_aux_sym_token6] = SHIFT(61),
    },
    
    [61] = {    
        [ts_aux_sym_token6] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    
    [62] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(63),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [63] = {    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 3),
    },
    
    [64] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 2),
    },
    
    [65] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(66),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [66] = {    
        [ts_aux_sym_token6] = SHIFT(67),
    },
    
    [67] = {    
        [ts_aux_sym_token11] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_object, 4),
    },
    
    [68] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_array, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_array, 2),
    },
    
    [69] = {    
        [ts_sym_string] = SHIFT(70),    
        [ts_aux_sym_token6] = SHIFT(75),    
        [ts_builtin_sym_error] = SHIFT(76),
    },
    
    [70] = {    
        [ts_aux_sym_token8] = SHIFT(71),
    },
    
    [71] = {    
        [ts_sym_array] = SHIFT(37),    
        [ts_sym_expression] = SHIFT(72),    
        [ts_sym_false] = SHIFT(37),    
        [ts_sym_identifier] = SHIFT(46),    
        [ts_sym_literal] = SHIFT(46),    
        [ts_sym_null] = SHIFT(37),    
        [ts_sym_number] = SHIFT(37),    
        [ts_sym_object] = SHIFT(37),    
        [ts_sym_string] = SHIFT(37),    
        [ts_sym_true] = SHIFT(37),    
        [ts_aux_sym_token10] = SHIFT(47),    
        [ts_aux_sym_token5] = SHIFT(52),
    },
    
    [72] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(73),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [73] = {    
        [ts_aux_sym_token6] = SHIFT(74),
    },
    
    [74] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 6),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 6),
    },
    
    [75] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 2),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 2),
    },
    
    [76] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(77),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [77] = {    
        [ts_aux_sym_token6] = SHIFT(78),
    },
    
    [78] = {    
        [ts_aux_sym_token1] = REDUCE(ts_sym_object, 4),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_object, 4),
    },
    
    [79] = {    
        [ts_sym__terminator] = SHIFT(80),    
        [ts_aux_sym_token1] = SHIFT(81),    
        [ts_aux_sym_token2] = SHIFT(81),
    },
    
    [80] = {    
        [ts_sym__IF] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__VAR] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement, 2),
    },
    
    [81] = {    
        [ts_sym__IF] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__VAR] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_false] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_null] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_number] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_string] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_true] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym__terminator, 1),
    },
    
    [82] = {    
        [ts_sym__IF] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__VAR] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement, 1),
    },
    
    [83] = {    
        [ts_sym__IF] = SHIFT(8),    
        [ts_sym__VAR] = SHIFT(14),    
        [ts_sym_array] = SHIFT(17),    
        [ts_sym_assignment] = SHIFT(79),    
        [ts_sym_expression] = SHIFT(79),    
        [ts_sym_false] = SHIFT(17),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(82),    
        [ts_sym_literal] = SHIFT(19),    
        [ts_sym_null] = SHIFT(17),    
        [ts_sym_number] = SHIFT(17),    
        [ts_sym_object] = SHIFT(17),    
        [ts_sym_statement] = SHIFT(83),    
        [ts_sym_string] = SHIFT(17),    
        [ts_sym_true] = SHIFT(17),    
        [ts_aux_sym_repeat_helper2] = SHIFT(84),    
        [ts_aux_sym_token10] = SHIFT(20),    
        [ts_aux_sym_token5] = SHIFT(69),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [84] = {    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    
    [85] = {    
        [ts_aux_sym_token6] = SHIFT(86),
    },
    
    [86] = {    
        [ts_sym__IF] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__VAR] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [87] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
    },
    
    [88] = {    
        [ts_sym_array] = SHIFT(21),    
        [ts_sym_expression] = SHIFT(89),    
        [ts_sym_false] = SHIFT(21),    
        [ts_sym_identifier] = SHIFT(28),    
        [ts_sym_literal] = SHIFT(28),    
        [ts_sym_null] = SHIFT(21),    
        [ts_sym_number] = SHIFT(21),    
        [ts_sym_object] = SHIFT(21),    
        [ts_sym_string] = SHIFT(21),    
        [ts_sym_true] = SHIFT(21),    
        [ts_aux_sym_token10] = SHIFT(29),    
        [ts_aux_sym_token11] = SHIFT(92),    
        [ts_aux_sym_token5] = SHIFT(34),    
        [ts_builtin_sym_error] = SHIFT(89),
    },
    
    [89] = {    
        [ts_aux_sym_repeat_helper4] = SHIFT(90),    
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym_repeat_helper4, 0),    
        [ts_aux_sym_token9] = SHIFT(25),
    },
    
    [90] = {    
        [ts_aux_sym_token11] = SHIFT(91),
    },
    
    [91] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 4),
    },
    
    [92] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_array, 2),
    },
    
    [93] = {    
        [ts_sym_string] = SHIFT(94),    
        [ts_aux_sym_token6] = SHIFT(99),    
        [ts_builtin_sym_error] = SHIFT(100),
    },
    
    [94] = {    
        [ts_aux_sym_token8] = SHIFT(95),
    },
    
    [95] = {    
        [ts_sym_array] = SHIFT(37),    
        [ts_sym_expression] = SHIFT(96),    
        [ts_sym_false] = SHIFT(37),    
        [ts_sym_identifier] = SHIFT(46),    
        [ts_sym_literal] = SHIFT(46),    
        [ts_sym_null] = SHIFT(37),    
        [ts_sym_number] = SHIFT(37),    
        [ts_sym_object] = SHIFT(37),    
        [ts_sym_string] = SHIFT(37),    
        [ts_sym_true] = SHIFT(37),    
        [ts_aux_sym_token10] = SHIFT(47),    
        [ts_aux_sym_token5] = SHIFT(52),
    },
    
    [96] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(97),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [97] = {    
        [ts_aux_sym_token6] = SHIFT(98),
    },
    
    [98] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 6),
    },
    
    [99] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 2),
    },
    
    [100] = {    
        [ts_aux_sym_repeat_helper3] = SHIFT(101),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper3, 0),    
        [ts_aux_sym_token9] = SHIFT(41),
    },
    
    [101] = {    
        [ts_aux_sym_token6] = SHIFT(102),
    },
    
    [102] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_object, 4),
    },
    
    [103] = {    
        [ts_aux_sym_token6] = SHIFT(104),
    },
    
    [104] = {    
        [ts_sym__IF] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym__VAR] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_false] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_null] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_number] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_string] = REDUCE(ts_sym_statement_block, 3),    
        [ts_sym_true] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement_block, 3),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 3),
    },
    
    [105] = {    
        [ts_sym__terminator] = SHIFT(106),    
        [ts_aux_sym_token1] = SHIFT(107),    
        [ts_aux_sym_token2] = SHIFT(107),
    },
    
    [106] = {    
        [ts_sym__IF] = REDUCE(ts_sym_statement, 2),    
        [ts_sym__VAR] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 2),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement, 2),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 2),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 2),
    },
    
    [107] = {    
        [ts_sym__IF] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym__VAR] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_false] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_null] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_number] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_string] = REDUCE(ts_sym__terminator, 1),    
        [ts_sym_true] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym__terminator, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__terminator, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym__terminator, 1),
    },
    
    [108] = {    
        [ts_sym__IF] = REDUCE(ts_sym_statement, 1),    
        [ts_sym__VAR] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_false] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_null] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),    
        [ts_sym_true] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token10] = REDUCE(ts_sym_statement, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement, 1),
    },
    
    [109] = {    
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    
    [110] = {    
        [ts_sym__IF] = SHIFT(1),    
        [ts_sym__VAR] = SHIFT(14),    
        [ts_sym_array] = SHIFT(17),    
        [ts_sym_assignment] = SHIFT(105),    
        [ts_sym_expression] = SHIFT(105),    
        [ts_sym_false] = SHIFT(17),    
        [ts_sym_identifier] = SHIFT(19),    
        [ts_sym_if_statement] = SHIFT(108),    
        [ts_sym_literal] = SHIFT(19),    
        [ts_sym_null] = SHIFT(17),    
        [ts_sym_number] = SHIFT(17),    
        [ts_sym_object] = SHIFT(17),    
        [ts_sym_statement] = SHIFT(110),    
        [ts_sym_string] = SHIFT(17),    
        [ts_sym_true] = SHIFT(17),    
        [ts_aux_sym_repeat_helper1] = SHIFT(111),    
        [ts_aux_sym_token10] = SHIFT(20),    
        [ts_aux_sym_token5] = SHIFT(69),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    
    [111] = {    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    
    [112] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

EXPORT_PARSER(ts_parser_javascript);
