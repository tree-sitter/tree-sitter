#include "runtime_spec_helper.h"

extern "C" ts_parser ts_parser_json();

START_TEST

describe("tracking the positions of AST nodes", []() {
    ts_document *doc;

    before_each([&]() {
        doc = ts_document_make();
        ts_document_set_parser(doc, ts_parser_json());
    });

    after_each([&]() {
        ts_document_free(doc);
    });

    it("records the widths and offsets of nodes", [&]() {
        ts_document_set_input_string(doc, "  [12, 5]");
        const ts_tree *tree = ts_document_tree(doc);

        const ts_tree *array = ts_tree_children(tree, NULL)[0];
        const ts_tree *number1 = ts_tree_children(array, NULL)[0];
        const ts_tree *number2 = ts_tree_children(array, NULL)[1];

        AssertThat(ts_document_symbol_name(doc, array), Equals("array"));
        AssertThat(ts_document_symbol_name(doc, number1), Equals("value"));
        AssertThat(ts_document_symbol_name(doc, number2), Equals("value"));

        AssertThat(ts_tree_offset(number1), Equals<size_t>(0));
        AssertThat(ts_tree_size(number1), Equals<size_t>(2));

        AssertThat(ts_tree_offset(number2), Equals<size_t>(1));
        AssertThat(ts_tree_size(number2), Equals<size_t>(1));

        AssertThat(ts_tree_offset(array), Equals<size_t>(2));
        AssertThat(ts_tree_size(array), Equals<size_t>(7));

        AssertThat(ts_tree_offset(tree), Equals<size_t>(2));
        AssertThat(ts_tree_size(tree), Equals<size_t>(7));
    });
});

END_TEST
