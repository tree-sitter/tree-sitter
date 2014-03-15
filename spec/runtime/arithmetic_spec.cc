#include "runtime_spec_helper.h"

extern "C" ts_parser ts_parser_arithmetic();

START_TEST

describe("arithmetic", []() {
    ts_document *doc;

    before_each([&]() {
        doc = ts_document_make();
        ts_document_set_parser(doc, ts_parser_arithmetic());
    });

    after_each([&]() {
        ts_document_free(doc);
    });

    it("parses variables", [&]() {
        ts_document_set_input_string(doc, "x");
        AssertThat(string(ts_document_string(doc)), Equals(
            "(expression (term (factor (variable))))"));
    });

    it("parses numbers", [&]() {
        ts_document_set_input_string(doc, "5");
        AssertThat(string(ts_document_string(doc)), Equals(
            "(expression (term (factor (number))))"));
    });

    it("parses products of variables", [&]() {
        ts_document_set_input_string(doc, "x + y");
        AssertThat(string(ts_document_string(doc)), Equals(
            "(expression (term (factor (variable))) (plus) (term (factor (variable))))"));

        ts_document_set_input_string(doc, "x * y");
        AssertThat(string(ts_document_string(doc)), Equals(
            "(expression (term (factor (variable)) (times) (factor (variable))))"));
    });

    it("parses complex trees", [&]() {
        ts_document_set_input_string(doc, "x * y + z * a");
        AssertThat(string(ts_document_string(doc)), Equals(
            "(expression (term (factor (variable)) (times) (factor (variable))) (plus) (term (factor (variable)) (times) (factor (variable))))"));

        ts_document_set_input_string(doc, "x * (y + z)");
        AssertThat(string(ts_document_string(doc)), Equals(
            "(expression (term (factor (variable)) (times) (factor (expression (term (factor (variable))) (plus) (term (factor (variable)))))))"));
    });

    describe("error recovery", [&]() {
        it("recovers from errors at the top level", [&]() {
            ts_document_set_input_string(doc, "x * * y");
            AssertThat(string(ts_document_string(doc)), Equals("(ERROR)"));
        });

        it("recovers from errors in parenthesized expressions", [&]() {
            ts_document_set_input_string(doc, "x + (y * + z) * 5");
            AssertThat(string(ts_document_string(doc)), Equals(
                "(expression (term (factor (variable))) (plus) (term (factor (ERROR)) (times) (factor (number))))"));
        });
    });
});

END_TEST