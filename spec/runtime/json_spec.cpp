#include "spec_helper.h"

extern ts_parse_config ts_parse_config_json;

START_TEST

describe("json", []() {
    ts_document *document;
    
    before_each([&]() {
        document = ts_document_make();
        ts_document_set_parser(document, ts_parse_config_json);
    });
    
    it("parses strings", [&]() {
        ts_document_set_text(document, "\"\"");
        AssertThat(string(ts_document_string(document)), Equals("(value (string))"));

        ts_document_set_text(document, "\"simple-string\"");
        AssertThat(string(ts_document_string(document)), Equals("(value (string))"));

        ts_document_set_text(document, "\"this is a \\\"string\\\" within a string\"");
        AssertThat(string(ts_document_string(document)), Equals("(value (string))"));
    });
    
    it("parses objects", [&]() {
        ts_document_set_text(document, "{}");
        AssertThat(string(ts_document_string(document)), Equals("(value (object))"));

        ts_document_set_text(document, "{ \"key1\": 1 }");
        AssertThat(string(ts_document_string(document)), Equals("(value (object (string) (value (number))))"));

        ts_document_set_text(document, "{\"key1\": 1, \"key2\": 2 }");
        AssertThat(string(ts_document_string(document)), Equals("(value (object (string) (value (number)) (string) (value (number))))"));
    });
    
    it("parses arrays", [&]() {
        ts_document_set_text(document, "[]");
        AssertThat(string(ts_document_string(document)), Equals("(value (array))"));

        ts_document_set_text(document, "[5]");
        AssertThat(string(ts_document_string(document)), Equals("(value (array (value (number))))"));

        ts_document_set_text(document, "[1, 2, 3]");
        AssertThat(string(ts_document_string(document)), Equals("(value (array (value (number)) (value (number)) (value (number))))"));
    });
});

END_TEST