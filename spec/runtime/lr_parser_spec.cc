#include "runtime_spec_helper.h"
#include "helpers/spy_reader.h"
#include "helpers/dummy_parser.h"
#include "tree_sitter/parser/lr_parser.h"

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
        parser = ts_lr_parser_make(dummy_parser.symbol_count,
                                   (const ts_parse_action *)dummy_parser.parse_table,
                                   dummy_parser.lex_states,
                                   fake_lex,
                                   dummy_parser.hidden_symbols,
                                   nullptr);
    });

    after_each([&]() {
        delete reader;
    });

    describe("when starting at the beginning of the input (edit is NULL)", [&]() {
        before_each([&]() {
            ts_lr_parser_initialize(parser, reader->input, nullptr);
        });

        it("runs the lexer with the lex state corresponding to the initial state", [&]() {
            lex_fn_node_to_return = ts_tree_make_leaf(dummy_sym2, 5, 1);
            ts_lr_parser_parse(parser, nullptr);
            AssertThat(lex_fn_state_received, Equals(100));
        });

        describe("when the returned symbol indicates a shift action", [&]() {
            before_each([&]() {
                lex_fn_node_to_return = ts_tree_make_leaf(dummy_sym2, 5, 1);
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
                lex_fn_node_to_return = ts_tree_make_leaf(dummy_sym1, 5, 1);
            });

            it("ends the parse, returning an error tree", [&]() {
                auto result = ts_lr_parser_parse(parser, nullptr);
                AssertThat(ts_tree_symbol(result), Equals(ts_builtin_sym_error));
            });
        });
    });
});

END_TEST