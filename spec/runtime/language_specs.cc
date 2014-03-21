#include "runtime_spec_helper.h"
#include "helpers/read_test_entries.h"

extern "C" ts_parser ts_parser_json();
extern "C" ts_parser ts_parser_arithmetic();

START_TEST

describe("Languages", [&]() {
    ts_document *doc;

    before_each([&]() {
        doc = ts_document_make();
    });

    after_each([&]() {
        ts_document_free(doc);
    });

    auto run_tests_for_language = [&](string language) {
        for (auto &entry : test_entries_for_language(language)) {
            it(entry.description.c_str(), [&]() {
                ts_document_set_input_string(doc, entry.input.c_str());
                AssertThat(ts_document_string(doc), Equals(entry.tree_string.c_str()));
            });
        }
    };

    describe("json", [&]() {
        before_each([&]() {
            ts_document_set_parser(doc, ts_parser_json());
        });

        run_tests_for_language("json");
    });

    describe("arithmetic", [&]() {
        before_each([&]() {
            ts_document_set_parser(doc, ts_parser_arithmetic());
        });

        run_tests_for_language("arithmetic");
    });
});

END_TEST