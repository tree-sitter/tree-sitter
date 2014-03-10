#include "runtime_spec_helper.h"
#include "helpers/spy_reader.h"

extern ts_parse_config ts_parse_config_json;

START_TEST

describe("reading from an input", [&]() {
    ts_document *doc;
    
    before_each([&]() {
        doc = ts_document_make();
        ts_document_set_parser(doc, ts_parse_config_json);
    });
    
    after_each([&]() {
        ts_document_free(doc);
    });

    it("reads the entire input", [&]() {
        SpyReader reader("\"ok go do it!\"", 3);
        ts_document_set_input(doc, reader.input);
        
        AssertThat(string(ts_document_string(doc)), Equals("(value (string))"));
        AssertThat(reader.chunks_read, Equals(vector<string>({
            "\"ok",
            " go",
            " do",
            " it",
            "!\"",
            ""
        })));
    });
});

END_TEST