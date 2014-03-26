#include "tree_sitter/parser.h"

#define TS_SYMBOL_COUNT 11

enum {
    ts_sym_expression = 2,
    ts_sym_factor = 3,
    ts_sym_number = 4,
    ts_sym_plus = 5,
    ts_sym_term = 6,
    ts_sym_times = 7,
    ts_sym_variable = 8,
    ts_aux_sym_token1 = 9,
    ts_aux_sym_token2 = 10,
};

SYMBOL_NAMES = {
    "error",
    "end",
    "expression",
    "factor",
    "number",
    "plus",
    "term",
    "times",
    "variable",
    "token1",
    "token2",
};

HIDDEN_SYMBOLS(11) = {    
    [ts_aux_sym_token1] = 1,    
    [ts_aux_sym_token2] = 1,
};

LEX_FN() {
    START_LEXER();
    switch (lex_state) {
        case 0:
            LEX_ERROR();
        case 1:
            if (lookahead == '+')
                ADVANCE(2);
            LEX_ERROR();
        case 2:
            ACCEPT_TOKEN(ts_sym_plus);
        case 3:
            if (lookahead == ')')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 5:
            if (lookahead == ')')
                ADVANCE(4);
            if (lookahead == '+')
                ADVANCE(2);
            LEX_ERROR();
        case 6:
            if (lookahead == ')')
                ADVANCE(4);
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '+')
                ADVANCE(2);
            LEX_ERROR();
        case 7:
            ACCEPT_TOKEN(ts_sym_times);
        case 8:
            if (lookahead == '(')
                ADVANCE(9);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            LEX_ERROR();
        case 9:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 10:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym_number);
        case 11:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(11);
            ACCEPT_TOKEN(ts_sym_number);
        case 12:
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_variable);
        case 13:
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym_variable);
        case 14:
            if (lookahead == ')')
                ADVANCE(4);
            if (lookahead == '*')
                ADVANCE(7);
            LEX_ERROR();
        case 15:
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '+')
                ADVANCE(2);
            LEX_ERROR();
        case 16:
            if (lookahead == '*')
                ADVANCE(7);
            LEX_ERROR();
        case ts_lex_state_error:
            if (lookahead == '(')
                ADVANCE(9);
            if (lookahead == ')')
                ADVANCE(4);
            if (lookahead == '*')
                ADVANCE(7);
            if (lookahead == '+')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(12);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES(52) = {
    [0] = 8,
    [1] = 0,
    [2] = 15,
    [3] = 8,
    [4] = 1,
    [5] = 1,
    [6] = 8,
    [7] = 3,
    [8] = 1,
    [9] = 6,
    [10] = 8,
    [11] = 5,
    [12] = 5,
    [13] = 8,
    [14] = 3,
    [15] = 5,
    [16] = 6,
    [17] = 5,
    [18] = 8,
    [19] = 14,
    [20] = 8,
    [21] = 3,
    [22] = 3,
    [23] = 8,
    [24] = 3,
    [25] = 3,
    [26] = 8,
    [27] = 3,
    [28] = 6,
    [29] = 14,
    [30] = 3,
    [31] = 8,
    [32] = 3,
    [33] = 14,
    [34] = 15,
    [35] = 1,
    [36] = 8,
    [37] = 16,
    [38] = 8,
    [39] = 0,
    [40] = 0,
    [41] = 8,
    [42] = 3,
    [43] = 0,
    [44] = 16,
    [45] = 0,
    [46] = 8,
    [47] = 3,
    [48] = 16,
    [49] = 8,
    [50] = 3,
    [51] = 15,
};

PARSE_TABLE(52, 11) = {
    [0] = {    
        [ts_sym_expression] = SHIFT(1),    
        [ts_sym_factor] = SHIFT(2),    
        [ts_sym_number] = SHIFT(34),    
        [ts_sym_term] = SHIFT(35),    
        [ts_sym_variable] = SHIFT(34),    
        [ts_aux_sym_token1] = SHIFT(49),
    },
    
    [1] = {    
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    
    [2] = {    
        [ts_sym_plus] = REDUCE(ts_sym_term, 1),    
        [ts_sym_times] = SHIFT(3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_term, 1),
    },
    
    [3] = {    
        [ts_sym_factor] = SHIFT(4),    
        [ts_sym_number] = SHIFT(5),    
        [ts_sym_variable] = SHIFT(5),    
        [ts_aux_sym_token1] = SHIFT(6),
    },
    
    [4] = {    
        [ts_sym_plus] = REDUCE(ts_sym_term, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_term, 3),
    },
    
    [5] = {    
        [ts_sym_plus] = REDUCE(ts_sym_factor, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_factor, 1),
    },
    
    [6] = {    
        [ts_sym_expression] = SHIFT(7),    
        [ts_sym_factor] = SHIFT(9),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_term] = SHIFT(17),    
        [ts_sym_variable] = SHIFT(16),    
        [ts_aux_sym_token1] = SHIFT(26),    
        [ts_builtin_sym_error] = SHIFT(7),
    },
    
    [7] = {    
        [ts_aux_sym_token2] = SHIFT(8),
    },
    
    [8] = {    
        [ts_sym_plus] = REDUCE(ts_sym_factor, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_factor, 3),
    },
    
    [9] = {    
        [ts_sym_plus] = REDUCE(ts_sym_term, 1),    
        [ts_sym_times] = SHIFT(10),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_term, 1),
    },
    
    [10] = {    
        [ts_sym_factor] = SHIFT(11),    
        [ts_sym_number] = SHIFT(12),    
        [ts_sym_variable] = SHIFT(12),    
        [ts_aux_sym_token1] = SHIFT(13),
    },
    
    [11] = {    
        [ts_sym_plus] = REDUCE(ts_sym_term, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_term, 3),
    },
    
    [12] = {    
        [ts_sym_plus] = REDUCE(ts_sym_factor, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_factor, 1),
    },
    
    [13] = {    
        [ts_sym_expression] = SHIFT(14),    
        [ts_sym_factor] = SHIFT(9),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_term] = SHIFT(17),    
        [ts_sym_variable] = SHIFT(16),    
        [ts_aux_sym_token1] = SHIFT(26),    
        [ts_builtin_sym_error] = SHIFT(14),
    },
    
    [14] = {    
        [ts_aux_sym_token2] = SHIFT(15),
    },
    
    [15] = {    
        [ts_sym_plus] = REDUCE(ts_sym_factor, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_factor, 3),
    },
    
    [16] = {    
        [ts_sym_plus] = REDUCE(ts_sym_factor, 1),    
        [ts_sym_times] = REDUCE(ts_sym_factor, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_factor, 1),
    },
    
    [17] = {    
        [ts_sym_plus] = SHIFT(18),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
    },
    
    [18] = {    
        [ts_sym_factor] = SHIFT(19),    
        [ts_sym_number] = SHIFT(29),    
        [ts_sym_term] = SHIFT(30),    
        [ts_sym_variable] = SHIFT(29),    
        [ts_aux_sym_token1] = SHIFT(31),
    },
    
    [19] = {    
        [ts_sym_times] = SHIFT(20),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_term, 1),
    },
    
    [20] = {    
        [ts_sym_factor] = SHIFT(21),    
        [ts_sym_number] = SHIFT(22),    
        [ts_sym_variable] = SHIFT(22),    
        [ts_aux_sym_token1] = SHIFT(23),
    },
    
    [21] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_term, 3),
    },
    
    [22] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_factor, 1),
    },
    
    [23] = {    
        [ts_sym_expression] = SHIFT(24),    
        [ts_sym_factor] = SHIFT(9),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_term] = SHIFT(17),    
        [ts_sym_variable] = SHIFT(16),    
        [ts_aux_sym_token1] = SHIFT(26),    
        [ts_builtin_sym_error] = SHIFT(24),
    },
    
    [24] = {    
        [ts_aux_sym_token2] = SHIFT(25),
    },
    
    [25] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_factor, 3),
    },
    
    [26] = {    
        [ts_sym_expression] = SHIFT(27),    
        [ts_sym_factor] = SHIFT(9),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_term] = SHIFT(17),    
        [ts_sym_variable] = SHIFT(16),    
        [ts_aux_sym_token1] = SHIFT(26),    
        [ts_builtin_sym_error] = SHIFT(27),
    },
    
    [27] = {    
        [ts_aux_sym_token2] = SHIFT(28),
    },
    
    [28] = {    
        [ts_sym_plus] = REDUCE(ts_sym_factor, 3),    
        [ts_sym_times] = REDUCE(ts_sym_factor, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_factor, 3),
    },
    
    [29] = {    
        [ts_sym_times] = REDUCE(ts_sym_factor, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_factor, 1),
    },
    
    [30] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 3),
    },
    
    [31] = {    
        [ts_sym_expression] = SHIFT(32),    
        [ts_sym_factor] = SHIFT(9),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_term] = SHIFT(17),    
        [ts_sym_variable] = SHIFT(16),    
        [ts_aux_sym_token1] = SHIFT(26),    
        [ts_builtin_sym_error] = SHIFT(32),
    },
    
    [32] = {    
        [ts_aux_sym_token2] = SHIFT(33),
    },
    
    [33] = {    
        [ts_sym_times] = REDUCE(ts_sym_factor, 3),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_factor, 3),
    },
    
    [34] = {    
        [ts_sym_plus] = REDUCE(ts_sym_factor, 1),    
        [ts_sym_times] = REDUCE(ts_sym_factor, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_factor, 1),
    },
    
    [35] = {    
        [ts_sym_plus] = SHIFT(36),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
    },
    
    [36] = {    
        [ts_sym_factor] = SHIFT(37),    
        [ts_sym_number] = SHIFT(44),    
        [ts_sym_term] = SHIFT(45),    
        [ts_sym_variable] = SHIFT(44),    
        [ts_aux_sym_token1] = SHIFT(46),
    },
    
    [37] = {    
        [ts_sym_times] = SHIFT(38),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_term, 1),
    },
    
    [38] = {    
        [ts_sym_factor] = SHIFT(39),    
        [ts_sym_number] = SHIFT(40),    
        [ts_sym_variable] = SHIFT(40),    
        [ts_aux_sym_token1] = SHIFT(41),
    },
    
    [39] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_term, 3),
    },
    
    [40] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_factor, 1),
    },
    
    [41] = {    
        [ts_sym_expression] = SHIFT(42),    
        [ts_sym_factor] = SHIFT(9),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_term] = SHIFT(17),    
        [ts_sym_variable] = SHIFT(16),    
        [ts_aux_sym_token1] = SHIFT(26),    
        [ts_builtin_sym_error] = SHIFT(42),
    },
    
    [42] = {    
        [ts_aux_sym_token2] = SHIFT(43),
    },
    
    [43] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_factor, 3),
    },
    
    [44] = {    
        [ts_sym_times] = REDUCE(ts_sym_factor, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_factor, 1),
    },
    
    [45] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 3),
    },
    
    [46] = {    
        [ts_sym_expression] = SHIFT(47),    
        [ts_sym_factor] = SHIFT(9),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_term] = SHIFT(17),    
        [ts_sym_variable] = SHIFT(16),    
        [ts_aux_sym_token1] = SHIFT(26),    
        [ts_builtin_sym_error] = SHIFT(47),
    },
    
    [47] = {    
        [ts_aux_sym_token2] = SHIFT(48),
    },
    
    [48] = {    
        [ts_sym_times] = REDUCE(ts_sym_factor, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_factor, 3),
    },
    
    [49] = {    
        [ts_sym_expression] = SHIFT(50),    
        [ts_sym_factor] = SHIFT(9),    
        [ts_sym_number] = SHIFT(16),    
        [ts_sym_term] = SHIFT(17),    
        [ts_sym_variable] = SHIFT(16),    
        [ts_aux_sym_token1] = SHIFT(26),    
        [ts_builtin_sym_error] = SHIFT(50),
    },
    
    [50] = {    
        [ts_aux_sym_token2] = SHIFT(51),
    },
    
    [51] = {    
        [ts_sym_plus] = REDUCE(ts_sym_factor, 3),    
        [ts_sym_times] = REDUCE(ts_sym_factor, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_factor, 3),
    },
};

EXPORT_PARSER(ts_parser_arithmetic);
