#include "runtime_spec_helper.h"

extern "C" ts_parser ts_parser_json();

START_TEST

describe("json", []() {
    ts_document *doc;

    before_each([&]() {
        doc = ts_document_make();
        ts_document_set_parser(doc, ts_parser_json());
    });

    after_each([&]() {
        ts_document_free(doc);
    });

    it("parses strings", [&]() {
        ts_document_set_input_string(doc, "\"\"");
        AssertThat(string(ts_document_string(doc)), Equals("(value (string))"));

        ts_document_set_input_string(doc, "\"simple-string\"");
        AssertThat(string(ts_document_string(doc)), Equals("(value (string))"));

        ts_document_set_input_string(doc, "\"this is a \\\"string\\\" within a string\"");
        AssertThat(string(ts_document_string(doc)), Equals("(value (string))"));
    });

    it("parses objects", [&]() {
        ts_document_set_input_string(doc, "{}");
        AssertThat(string(ts_document_string(doc)), Equals("(value (object))"));

        ts_document_set_input_string(doc, "{ \"key1\": 1 }");
        AssertThat(string(ts_document_string(doc)), Equals("(value (object (string) (value (number))))"));

        ts_document_set_input_string(doc, "{\"key1\": 1, \"key2\": 2 }");
        AssertThat(string(ts_document_string(doc)), Equals("(value (object (string) (value (number)) (string) (value (number))))"));
    });

    it("parses arrays", [&]() {
        ts_document_set_input_string(doc, "[]");
        AssertThat(string(ts_document_string(doc)), Equals("(value (array))"));

        ts_document_set_input_string(doc, "[5]");
        AssertThat(string(ts_document_string(doc)), Equals("(value (array (value (number))))"));

        ts_document_set_input_string(doc, "[1, 2, 3]");
        AssertThat(string(ts_document_string(doc)), Equals("(value (array (value (number)) (value (number)) (value (number))))"));
    });

    describe("tracking the positions of AST nodes", [&]() {
        it("records the widths and offsets of nodes", [&]() {
            ts_document_set_input_string(doc, "  [12, 5]");
            const ts_tree *tree = ts_document_tree(doc);

            // TODO - make this better
            const ts_tree *array = ts_tree_children(tree, NULL)[0];
            const ts_tree *number1 = ts_tree_children(ts_tree_children(array, NULL)[1], NULL)[0];
            const ts_tree *number2 = ts_tree_children(ts_tree_children(ts_tree_children(array, NULL)[2], NULL)[1], NULL)[0];

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

    describe("errors", [&]() {
        it("reports errors in the top-level node", [&]() {
            ts_document_set_input_string(doc, "[");
            AssertThat(string(ts_document_string(doc)), Equals("(ERROR)"));
        });

        it("reports errors inside of arrays and objects", [&]() {
            ts_document_set_input_string(doc, "{ \"key1\": 1, 5 }");
            AssertThat(string(ts_document_string(doc)), Equals("(value (object (string) (value (number)) (ERROR)))"));

            ts_document_set_input_string(doc, "[1,,2]");
            AssertThat(string(ts_document_string(doc)), Equals("(value (array (value (number)) (ERROR) (value (number))))"));
        });

        it("reports errors in nested objects", [&]() {
            ts_document_set_input_string(doc, "{ \"key1\": { \"key2\": 1, 2 }, [, \"key3\": 3 }");
            AssertThat(string(ts_document_string(doc)), Equals("(value (object (string) (value (object (string) (value (number)) (ERROR))) (ERROR) (string) (value (number))))"));
        });
    });
});

END_TEST