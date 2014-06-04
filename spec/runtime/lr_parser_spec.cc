#include "runtime_spec_helper.h"
#include "helpers/spy_reader.h"
#include "tree_sitter/parser/lr_parser.h"

enum {
    sym1 = 2,
    sym2 = 3,
    hidden_sym = 4,
};

const ts_parse_action parse_table[3][5] = {
    [0] = {
        [sym2] = SHIFT(12),
        [hidden_sym] = SHIFT(12),
    },
    [1] = {
        [sym1] = ACCEPT_INPUT(),
        [sym2] = SHIFT(2),
        [hidden_sym] = SHIFT(4),
    },
    [2] = {
        [sym1] = SHIFT(3),
        [sym2] = SHIFT(12),
        [hidden_sym] = SHIFT(12),
    },
};

ts_state_id lex_states[3] = {
    [0] = 100,
    [1] = 101,
    [2] = 102,
};

int hidden_symbols[5] = {
    [sym1] = 0,
    [sym2] = 0,
    [hidden_sym] = 1,
};

ts_tree *lex_fn_node_to_return;
ts_state_id lex_fn_state_received;
ts_lexer *lex_fn_lexer_received;

ts_tree * fake_lex(ts_lexer *lexer, ts_state_id state_id) {
    lex_fn_lexer_received = lexer;
    lex_fn_state_received = state_id;
    return lex_fn_node_to_return;
}

START_TEST

describe("LR Parsers", [&]() {
    ts_lr_parser *parser;
    SpyReader *reader;
    
    before_each([&]() {
        reader = new SpyReader("some structured text", 5);
        parser = ts_lr_parser_make(3, (const ts_parse_action *)parse_table, lex_states, fake_lex, hidden_symbols, nullptr);
    });
    
    after_each([&]() {
        delete reader;
    });
    
    describe("when starting at the beginning of the input (edit is NULL)", [&]() {
        before_each([&]() {
            ts_lr_parser_initialize(parser, reader->input, nullptr);
        });
        
        it("runs the lexer with the lex state corresponding to the initial state", [&]() {
            lex_fn_node_to_return = ts_tree_make_leaf(sym2, 5, 1);
            ts_lr_parser_parse(parser, nullptr);
            AssertThat(lex_fn_state_received, Equals(100));
        });

        describe("when the returned symbol indicates a shift action", [&]() {
            before_each([&]() {
                lex_fn_node_to_return = ts_tree_make_leaf(sym2, 5, 1);
            });
            
            it("advances to the state specified in the action", [&]() {
                ts_lr_parser_parse(parser, nullptr);
                AssertThat(ts_stack_top_state(&parser->stack), Equals(12));
            });
            
            it("continues parsing (returns NULL)", [&]() {
                auto result = ts_lr_parser_parse(parser, nullptr);
                AssertThat(result, Equals((ts_tree *)nullptr));
            });
        });
        
        describe("when the returned symbol indicates an error", [&]() {
            before_each([&]() {
                lex_fn_node_to_return = ts_tree_make_leaf(sym1, 5, 1);
            });
            
            it("ends the parse, returning an error tree", [&]() {
                auto result = ts_lr_parser_parse(parser, nullptr);
                AssertThat(ts_tree_symbol(result), Equals(ts_builtin_sym_error));
            });
        });
    });
});

END_TEST