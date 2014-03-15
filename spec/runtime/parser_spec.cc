#include "runtime_spec_helper.h"
#include "helpers/spy_reader.h"

extern "C" ts_parser ts_parser_json();
    
START_TEST

describe("parsing", [&]() {
    ts_document *doc;
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
            "(value "
                "(object "
                    "(string) "
                    "(value (array "
                        "(value (number)) "
                        "(value (number))))))"));
    });

    it("reads the entire input", [&]() {
        AssertThat(reader->chunks_read, Equals(vector<string>({
            "{ \"ke",
            "y\": [",
            "1, 2]",
            " }",
            ""
        })));
    });

    describe("modifying the input", [&]() {
        before_each([&]() {
            size_t position(string("{ \"key\": [1, 2]").length());
            string inserted_text(", \"key2\": 4 ");

            reader->content.insert(position, inserted_text);
            ts_document_edit(doc, position, 0, inserted_text.length());
        });

        it("updates the parse tree", [&]() {
            AssertThat(string(ts_document_string(doc)), Equals(
                "(value "
                    "(object "
                        "(string) "
                        "(value (array "
                            "(value (number)) "
                            "(value (number)))) "
                        "(string) "
                        "(value (number))))"
            ));
        });

        it_skip("re-reads only the changed portion of the input", [&]() {
            AssertThat(reader->chunks_read, Equals(vector<string>({
                ""
            })));
        });
    });
});

END_TEST
