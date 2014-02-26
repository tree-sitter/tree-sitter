#include "spec_helper.h"

extern ts_parse_config ts_parse_config_json;

START_TEST

describe("json", []() {
    ts_document *doc;
    
    before_each([&]() {
        doc = ts_document_make();
        ts_document_set_parser(doc, ts_parse_config_json);
    });
    
    after_each([&]() {
        ts_document_free(doc);
    });
    
    it("parses strings", [&]() {
        ts_document_set_text(doc, "\"\"");
        AssertThat(string(ts_document_string(doc)), Equals("(value (string))"));

        ts_document_set_text(doc, "\"simple-string\"");
        AssertThat(string(ts_document_string(doc)), Equals("(value (string))"));

        ts_document_set_text(doc, "\"this is a \\\"string\\\" within a string\"");
        AssertThat(string(ts_document_string(doc)), Equals("(value (string))"));
    });
    
    it("parses objects", [&]() {
        ts_document_set_text(doc, "{}");
        AssertThat(string(ts_document_string(doc)), Equals("(value (object))"));

        ts_document_set_text(doc, "{ \"key1\": 1 }");
        AssertThat(string(ts_document_string(doc)), Equals("(value (object (string) (value (number))))"));

        ts_document_set_text(doc, "{\"key1\": 1, \"key2\": 2 }");
        AssertThat(string(ts_document_string(doc)), Equals("(value (object (string) (value (number)) (string) (value (number))))"));
    });
    
    it("parses arrays", [&]() {
        ts_document_set_text(doc, "[]");
        AssertThat(string(ts_document_string(doc)), Equals("(value (array))"));

        ts_document_set_text(doc, "[5]");
        AssertThat(string(ts_document_string(doc)), Equals("(value (array (value (number))))"));

        ts_document_set_text(doc, "[1, 2, 3]");
        AssertThat(string(ts_document_string(doc)), Equals("(value (array (value (number)) (value (number)) (value (number))))"));
    });
    
    describe("errors", [&]() {
        it("reports errors in the top-level node", [&]() {
            ts_document_set_text(doc, "[");
            AssertThat(string(ts_document_string(doc)), Equals("(ERROR)"));

            ts_document_set_text(doc, "{ \"key1\": 1, ");
            AssertThat(string(ts_document_string(doc)), Equals("(ERROR)"));
        });
    });
});

END_TEST