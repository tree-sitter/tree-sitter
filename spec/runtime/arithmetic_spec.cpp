#include "spec_helper.h"
#include "document.h"

extern TSParseConfig ts_parse_config_arithmetic;

START_TEST

describe("arithmetic", []() {
    it("parses_numbers", [&]() {
        TSDocument *document = TSDocumentMake();
        TSDocumentSetUp(document, ts_parse_config_arithmetic);
        TSDocumentSetText(document, "w");
        printf("%s", TSDocumentToString(document));
    });
});

END_TEST