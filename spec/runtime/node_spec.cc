#include "runtime/runtime_spec_helper.h"

extern "C" TSParser * ts_parser_arithmetic();

START_TEST

describe("Node", []() {
    TSDocument *document;

    before_each([&]() {
        document = ts_document_make();
        ts_document_set_parser(document, ts_parser_arithmetic());
    });

    after_each([&]() {
        ts_document_free(document);
    });

    describe("getting the nth child node", [&]() {
        TSNode *root;

        describe("when the child has more than n visible children", [&]() {
            before_each([&]() {
                ts_document_set_input_string(document, "x + 1");
                root = ts_document_root_node(document);

                AssertThat(ts_node_name(root), Equals("sum"));
                AssertThat(ts_node_string(root), Equals("(sum (variable) (number))"));
            });

            after_each([&]() {
                ts_node_release(root);
            });

            it("returns the nth child", [&]() {
                TSNode *child1 = ts_node_child(root, 0);
                AssertThat(ts_node_name(child1), Equals("variable"));

                TSNode *child2 = ts_node_child(root, 1);
                AssertThat(ts_node_name(child2), Equals("number"));

                ts_node_release(child1);
                ts_node_release(child2);
            });
        });
    });

    it("gets the first token", [&]() {
        // ts_document_get_node(document, 0);
    });
});

END_TEST
