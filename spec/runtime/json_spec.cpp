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
        TSDocumentSetText(document, "{\"key1\":1,\"key2\":2}");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (object (token5) (string) (token6) (value (number)) (repeat_helper1 (token2) (string) (token6) (value (number))) (token7)))"));
        
        TSDocumentSetText(document, "{\"key1\":1}");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (object (token5) (string) (token6) (value (number)) (token3) (token7)))"));
    });
    
    it("parses arrays", [&]() {
        TSDocumentSetText(document, "[1,2,3]");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (array (token1) (value (number)) (repeat_helper2 (token2) (value (number)) (repeat_helper2 (token2) (value (number)))) (token4)))"));
    });
});

END_TEST