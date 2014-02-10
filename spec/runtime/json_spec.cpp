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
        TSDocumentSetText(document, "\"this is a \\\"string\\\"  \"");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (string))"));
    });
    
    it("parses objects", [&]() {
        TSDocumentSetText(document, "{\"key1\":1,\"key2\":2}");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (object (string) (value (number)) (string) (value (number))))"));
        
        TSDocumentSetText(document, "{\"key1\":1}");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (object (string) (value (number))))"));
    });
    
    it("parses arrays", [&]() {
        TSDocumentSetText(document, "[1,2,3]");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (array (value (number)) (value (number)) (value (number))))"));
    });
});

END_TEST