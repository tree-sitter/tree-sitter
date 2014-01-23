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
        TSDocumentSetText(document, "\"foo\"");
        AssertThat(string(TSDocumentToString(document)), Equals("(value (string))"));
    });
});

END_TEST