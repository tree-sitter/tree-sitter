#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/spy_reader.h"
#include "runtime/tree.h"

extern "C" TSParser * ts_parser_json();

START_TEST

describe("incremental parsing", [&]() {
    TSDocument *doc;

    before_each([&]() {
        doc = ts_document_make();
        ts_document_set_parser(doc, ts_parser_json());
    });

    after_each([&]() {
        ts_document_free(doc);
    });

    describe("incremental parsing", [&]() {
        SpyReader *reader;

        before_each([&]() {
            reader = new SpyReader("{ \"key\": [1, 2] }", 5);
            ts_document_set_input(doc, reader->input);
        });

        after_each([&]() {
            delete reader;
        });

        it("parses the input", [&]() {
            AssertThat(string(ts_document_string(doc)), Equals(
                "(object (string) (array (number) (number)))"));
        });

        it("reads the entire input", [&]() {
            AssertThat(reader->strings_read, Equals(vector<string>({
                "{ \"key\": [1, 2] }"
            })));
        });

        describe("modifying the end of the input", [&]() {
            before_each([&]() {
                size_t position(string("{ \"key\": [1, 2]").length());
                string inserted_text(", \"key2\": 4");

                reader->content.insert(position, inserted_text);
                ts_document_edit(doc, { position, 0, inserted_text.length() });
            });

            it("updates the parse tree", [&]() {
                AssertThat(string(ts_document_string(doc)), Equals(
                    "(object (string) (array (number) (number)) (string) (number))"));
            });

            it("re-reads only the changed portion of the input", [&]() {
                AssertThat(reader->strings_read.size(), Equals<size_t>(2));
                AssertThat(reader->strings_read[1], Equals(", \"key2\": 4 }"));
            });
        });

        describe("modifying the beginning of the input", [&]() {
            before_each([&]() {
                size_t position(string("{ ").length());
                string inserted_text("\"key2\": 4, ");

                reader->content.insert(position, inserted_text);
                ts_document_edit(doc, { position, 0, inserted_text.length() });
            });

            it("updates the parse tree", [&]() {
                AssertThat(string(ts_document_string(doc)), Equals(
                    "(object (string) (number) (string) (array (number) (number)))"));
            });

            it_skip("re-reads only the changed portion of the input", [&]() {
                AssertThat(reader->strings_read.size(), Equals<size_t>(2));
                AssertThat(reader->strings_read[1], Equals("\"key2\": 4, "));
            });
        });
    });

    it("records the widths and offsets of nodes", [&]() {
        ts_document_set_input_string(doc, "  [12, 5, 345]");

        TSNode *array = ts_document_root_node(doc);
        TSNode *number1 = ts_node_child(array, 0);
        TSNode *number2 = ts_node_child(array, 1);
        TSNode *number3 = ts_node_child(array, 2);

        AssertThat(ts_node_name(array), Equals("array"));
        AssertThat(ts_node_name(number1), Equals("number"));
        AssertThat(ts_node_name(number2), Equals("number"));

        AssertThat(ts_node_pos(array), Equals<size_t>(2));
        AssertThat(ts_node_size(array), Equals<size_t>(12));

        AssertThat(ts_node_pos(number1), Equals<size_t>(3));
        AssertThat(ts_node_size(number1), Equals<size_t>(2));

        AssertThat(ts_node_pos(number2), Equals<size_t>(7));
        AssertThat(ts_node_size(number2), Equals<size_t>(1));

        AssertThat(ts_node_pos(number3), Equals<size_t>(10));
        AssertThat(ts_node_size(number3), Equals<size_t>(3));

        ts_node_release(array);
        ts_node_release(number1);
        ts_node_release(number2);
        ts_node_release(number3);
    });
});

END_TEST
