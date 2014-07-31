#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/spy_reader.h"
#include "runtime/helpers/dummy_language.h"
#include "runtime/tree.h"
#include "runtime/parser.h"
#include "tree_sitter/parser.h"

TSTree *lex_fn_node_to_return;
TSStateId lex_fn_state_received;
TSLexer *lex_fn_lexer_received;

TSTree * fake_lex(TSLexer *lexer, TSStateId state_id) {
    lex_fn_lexer_received = lexer;
    lex_fn_state_received = state_id;
    return lex_fn_node_to_return;
}

START_TEST

describe("LR Parsers", [&]() {
    TSParser parser;
    SpyReader *reader;
    TSLanguage language;

    before_each([&]() {
        language = *dummy_language();
        language.lex_fn = fake_lex;
        parser = ts_parser_make(&language);

        reader = new SpyReader("some structured text", 5);
    });

    after_each([&]() {
        ts_parser_destroy(&parser);
        delete reader;
    });

    describe("when starting at the beginning of the input (edit is NULL)", [&]() {
        before_each([&]() {
            ts_parser_start(&parser, reader->input, nullptr);
        });

        it("runs the lexer with the lex state corresponding to the initial state", [&]() {
            lex_fn_node_to_return = ts_tree_make_leaf(dummy_sym2, 5, 1, 0);
            ts_parser_step(&parser);
            AssertThat(lex_fn_state_received, Equals(100));
        });

        describe("when the returned symbol indicates a shift action", [&]() {
            before_each([&]() {
                lex_fn_node_to_return = ts_tree_make_leaf(dummy_sym2, 5, 1, 0);
            });

            it("advances to the state specified in the action", [&]() {
                ts_parser_step(&parser);
                AssertThat(ts_stack_top_state(&parser.stack), Equals(12));
            });

            it("continues parsing (returns NULL)", [&]() {
                auto result = ts_parser_step(&parser);
                AssertThat(result, Equals((TSTree *)nullptr));
            });
        });

        describe("when the returned symbol indicates an error", [&]() {
            before_each([&]() {
                lex_fn_node_to_return = ts_tree_make_leaf(dummy_sym1, 5, 1, 0);
            });

            it("ends the parse, returning an error tree", [&]() {
                auto result = ts_parser_step(&parser);
                AssertThat(result->symbol, Equals(ts_builtin_sym_error));
            });
        });
    });
});

END_TEST
