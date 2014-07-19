#include "runtime/runtime_spec_helper.h"

extern "C" TSParser * ts_parser_json();

START_TEST

describe("Node", []() {
    TSDocument *document;
    TSNode *root;

    before_each([&]() {
        document = ts_document_make();
        ts_document_set_parser(document, ts_parser_json());

        ts_document_set_input_string(document, "  [12, 5, 345]");
        root = ts_document_root_node(document);
        AssertThat(ts_node_string(root), Equals("(array (number) (number) (number))"));
    });

    after_each([&]() {
        ts_document_free(document);
        ts_node_release(root);
    });

    it("knows its position and size", [&]() {
        TSNode *number1 = ts_node_child(root, 0);
        TSNode *number2 = ts_node_child(root, 1);
        TSNode *number3 = ts_node_child(root, 2);

        AssertThat(ts_node_name(root), Equals("array"));
        AssertThat(ts_node_name(number1), Equals("number"));
        AssertThat(ts_node_name(number2), Equals("number"));
        AssertThat(ts_node_name(number3), Equals("number"));

        AssertThat(ts_node_pos(root), Equals<size_t>(2));
        AssertThat(ts_node_size(root), Equals<size_t>(12));

        AssertThat(ts_node_pos(number1), Equals<size_t>(3));
        AssertThat(ts_node_size(number1), Equals<size_t>(2));

        AssertThat(ts_node_pos(number2), Equals<size_t>(7));
        AssertThat(ts_node_size(number2), Equals<size_t>(1));

        AssertThat(ts_node_pos(number3), Equals<size_t>(10));
        AssertThat(ts_node_size(number3), Equals<size_t>(3));

        ts_node_release(number1);
        ts_node_release(number2);
        ts_node_release(number3);
    });

    it("can retrieve its parent node", [&]() {
        TSNode *number2 = ts_node_child(root, 1);
        AssertThat(ts_node_parent(number2), Equals(root));

        ts_node_release(number2);
    });

    it("can retrieve its sibling nodes", [&]() {
        TSNode *number1 = ts_node_child(root, 0);
        TSNode *number2 = ts_node_child(root, 1);
        TSNode *number3 = ts_node_child(root, 2);

        AssertThat(ts_node_eq(ts_node_next_sibling(number2), number3), IsTrue());
        AssertThat(ts_node_eq(ts_node_prev_sibling(number2), number1), IsTrue());

        ts_node_release(number1);
        ts_node_release(number2);
        ts_node_release(number3);
    });

    describe("retrieving leaf nodes", [&]() {
        it("can retrieve the leaf node at a given position", [&]() {
            TSNode *number1 = ts_node_leaf_at_pos(root, 3);
            TSNode *number2 = ts_node_leaf_at_pos(root, 7);

            AssertThat(ts_node_name(number1), Equals("number"));
            AssertThat(ts_node_size(number1), Equals<size_t>(2));

            AssertThat(ts_node_name(number2), Equals("number"));
            AssertThat(ts_node_size(number2), Equals<size_t>(1));

            ts_node_release(number1);
            ts_node_release(number2);
        });

        it("returns higher-level nodes when no leaf is at the given position", [&]() {
            TSNode *node = ts_node_leaf_at_pos(root, 6);

            AssertThat(ts_node_name(node), Equals("array"));

            ts_node_release(node);
        });
    });
});

END_TEST
