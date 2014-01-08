#include "spec_helper.h"
#include "../fixtures/parsers/arithmetic.c"

START_TEST

describe("arithmetic", []() {
    it("parses_numbers", [&]() {
        TSDocument *document = TSDocumentMake();
        TSDocumentSetUp_arithmetic(document);
        TSDocumentSetText(document, "5");
        printf("%s", TSDocumentToString(document));
    });
});

END_TEST