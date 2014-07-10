#include "runtime/helpers/dummy_parser.h"
#include "tree_sitter/parser.h"

const TSParseAction parse_table[3][5] = {
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

TSParserConfig dummy_parser = {
    .symbol_count = 5,
    .parse_table = (const TSParseAction *)parse_table,
    .lex_states = lex_states,
    .hidden_symbol_flags = hidden_symbols,
};
