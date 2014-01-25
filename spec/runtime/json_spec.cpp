#include "spec_helper.h"
#include "document.h"

extern TSParseConfig ts_parse_config_json;

START_TEST

describe("json", []() {
    TSDocument *document;
    
    before_each([&]() {
        document = TSDocumentMake();
        TSDocumentSetUp(document, ts_parse_config_json);
    });
    
    it("parses strings", [&]() {
        TSDocumentSetText(document, "\"string\"");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (string))"));
    });
    
    it("parses objects", [&]() {
        TSDocumentSetText(document, "{\"key1\":1}");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (object (4) (string) (5) (value (number)) (2) (6)))"));

        TSDocumentSetText(document, "{\"key1\":1,\"key2\":2}");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (object (4) (string) (5) (value (number)) (6) (7)))"));
    });
});

END_TEST