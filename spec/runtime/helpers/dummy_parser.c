#include "runtime/helpers/dummy_parser.h"

const ts_parse_action parse_table[3][5] = {
    [0] = {
        [dummy_sym2] = SHIFT(12),
        [dummy_sym3] = SHIFT(12),
    },
    [1] = {
        [dummy_sym1] = ACCEPT_INPUT(),
        [dummy_sym2] = SHIFT(2),
        [dummy_sym3] = SHIFT(4),
    },
    [2] = {
        [dummy_sym1] = SHIFT(3),
        [dummy_sym2] = SHIFT(12),
        [dummy_sym3] = SHIFT(12),
    },
};

const TSStateId lex_states[3] = {
    [0] = 100,
    [1] = 101,
    [2] = 102,
};

const int hidden_symbols[5] = {
    [dummy_sym1] = 0,
    [dummy_sym2] = 0,
    [dummy_sym3] = 1,
};

struct test_parser dummy_parser = {
    .state_count = 3,
    .symbol_count = 5,
    .parse_table = (const ts_parse_action **)parse_table,
    .lex_states = lex_states,
    .hidden_symbols = hidden_symbols,
};
