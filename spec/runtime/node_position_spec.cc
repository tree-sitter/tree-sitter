#include "runtime/runtime_spec_helper.h"
#include "runtime/tree.h"

extern "C" TSParser * ts_parser_json();

START_TEST

describe("tracking the positions of AST nodes", []() {
    TSDocument *doc;

    before_each([&]() {
        doc = ts_document_make();
        ts_document_set_parser(doc, ts_parser_json());
    });

    after_each([&]() {
        ts_document_free(doc);
    });

    it("records the widths and offsets of nodes", [&]() {
        ts_document_set_input_string(doc, "  [12, 5]");

        const TSTree *tree = ts_document_tree(doc);
        const TSTree *array = tree->children[0];
        const TSTree *number1 = array->children[1]->children[0];
        const TSTree *number2 = array->children[2]->children[1]->children[0];

        AssertThat(ts_document_symbol_name(doc, array), Equals("array"));
        AssertThat(ts_document_symbol_name(doc, number1), Equals("number"));
        AssertThat(ts_document_symbol_name(doc, number2), Equals("number"));

        AssertThat(number1->offset, Equals<size_t>(0));
        AssertThat(number1->size, Equals<size_t>(2));

        AssertThat(number2->offset, Equals<size_t>(1));
        AssertThat(number2->size, Equals<size_t>(1));

        AssertThat(array->offset, Equals<size_t>(2));
        AssertThat(array->size, Equals<size_t>(7));

        AssertThat(tree->offset, Equals<size_t>(2));
        AssertThat(tree->size, Equals<size_t>(7));
    });
});

END_TEST
