#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/spy_reader.h"

extern "C" ts_parser ts_parser_json();

START_TEST

describe("incremental parsing", [&]() {
    TSDocument *doc;
    SpyReader *reader;

    before_each([&]() {
        doc = ts_document_make();
        ts_document_set_parser(doc, ts_parser_json());

        reader = new SpyReader("{ \"key\": [1, 2] }", 5);
        ts_document_set_input(doc, reader->input);
    });

    after_each([&]() {
        ts_document_free(doc);
        delete reader;
    });

    it("parses the input", [&]() {
        AssertThat(string(ts_document_string(doc)), Equals(
            "(value (object (string) (array (number) (number))))"));
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
                "(value (object (string) (array (number) (number)) (string) (number)))"));
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

        it("2 updates the parse tree", [&]() {
            AssertThat(string(ts_document_string(doc)), Equals(
                "(value (object (string) (number) (string) (array (number) (number))))"));
        });

        it_skip("re-reads only the changed portion of the input", [&]() {
            AssertThat(reader->strings_read.size(), Equals<size_t>(2));
            AssertThat(reader->strings_read[1], Equals("\"key2\": 4, "));
        });
    });

});

END_TEST
