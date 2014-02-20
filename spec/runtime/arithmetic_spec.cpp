#include "spec_helper.h"

extern ts_parse_config ts_parse_config_arithmetic;

START_TEST

describe("arithmetic", []() {
    ts_document *document;
    
    before_each([&]() {
        document = ts_document_make();
        ts_document_set_parser(document, ts_parse_config_arithmetic);
    });
    
    it("parses variables", [&]() {
        ts_document_set_text(document, "x");
        AssertThat(string(ts_document_string(document)), Equals(
            "(expression (term (factor (variable))))"));
    });
    
    it("parses numbers", [&]() {
        ts_document_set_text(document, "5");
        AssertThat(string(ts_document_string(document)), Equals(
            "(expression (term (factor (number))))"));
    });

    it("parses products of variables", [&]() {
        ts_document_set_text(document, "x + y");
        AssertThat(string(ts_document_string(document)), Equals(
            "(expression (term (factor (variable))) (plus) (term (factor (variable))))"));
        
        ts_document_set_text(document, "x * y");
        AssertThat(string(ts_document_string(document)), Equals(
            "(expression (term (factor (variable)) (times) (factor (variable))))"));
    });
    
    it("parses complex trees", [&]() {
        ts_document_set_text(document, "x * y + z * a");
        AssertThat(string(ts_document_string(document)), Equals(
            "(expression (term (factor (variable)) (times) (factor (variable))) (plus) (term (factor (variable)) (times) (factor (variable))))"));

        ts_document_set_text(document, "x * (y + z)");
        AssertThat(string(ts_document_string(document)), Equals(
            "(expression (term (factor (variable)) (times) (factor (expression (term (factor (variable))) (plus) (term (factor (variable)))))))"));
    });
});

END_TEST