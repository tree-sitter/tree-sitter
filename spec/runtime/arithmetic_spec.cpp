#include "spec_helper.h"
#include "document.h"

extern TSParseConfig ts_parse_config_arithmetic;

START_TEST

describe("arithmetic", []() {
    TSDocument *document;
    
    before_each([&]() {
        document = TSDocumentMake();
        TSDocumentSetUp(document, ts_parse_config_arithmetic);
    });
    
    it("parses variables", [&]() {
        TSDocumentSetText(document, "x");
        AssertThat(string(TSDocumentToString(document)), Equals(
            "(expression (term (factor (variable))))"));
    });

    it("parses products of variables", [&]() {
        TSDocumentSetText(document, "x*y");
        AssertThat(string(TSDocumentToString(document)), Equals(
            "(expression (term (factor (variable)) (3) (factor (variable))))"));
    });
    
    it("parses complex trees", [&]() {
        TSDocumentSetText(document, "x*y+z*a");
        AssertThat(string(TSDocumentToString(document)), Equals(
            "(expression (term (factor (variable)) (3) (factor (variable))) (4) (term (factor (variable)) (3) (factor (variable))))"));

        TSDocumentSetText(document, "x*(y+z)");
        AssertThat(string(TSDocumentToString(document)), Equals(
            "(expression (term (factor (variable)) (3) (factor (1) (expression (term (factor (variable))) (4) (term (factor (variable)))) (2))))"));
    });
});

END_TEST