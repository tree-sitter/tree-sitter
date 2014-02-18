#include "spec_helper.h"

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
    
    it("parses numbers", [&]() {
        TSDocumentSetText(document, "5");
        AssertThat(string(TSDocumentToString(document)), Equals(
            "(expression (term (factor (number))))"));
    });

    it("parses products of variables", [&]() {
        TSDocumentSetText(document, "x+y");
        AssertThat(string(TSDocumentToString(document)), Equals(
            "(expression (term (factor (variable))) (plus) (term (factor (variable))))"));
        
        TSDocumentSetText(document, "x*y");
        AssertThat(string(TSDocumentToString(document)), Equals(
            "(expression (term (factor (variable)) (times) (factor (variable))))"));
    });
    
    it("parses complex trees", [&]() {
        TSDocumentSetText(document, "x*y+z*a");
        AssertThat(string(TSDocumentToString(document)), Equals(
            "(expression (term (factor (variable)) (times) (factor (variable))) (plus) (term (factor (variable)) (times) (factor (variable))))"));

        TSDocumentSetText(document, "x*(y+z)");
        AssertThat(string(TSDocumentToString(document)), Equals(
            "(expression (term (factor (variable)) (times) (factor (expression (term (factor (variable))) (plus) (term (factor (variable)))))))"));
    });
});

END_TEST