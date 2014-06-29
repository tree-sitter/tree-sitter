#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/read_test_entries.h"

extern "C" TSParser ts_parser_javascript();
extern "C" TSParser ts_parser_json();
extern "C" TSParser ts_parser_arithmetic();
extern "C" TSParser ts_parser_golang();

START_TEST

describe("Languages", [&]() {
    TSDocument *doc;

    before_each([&]() {
        doc = ts_document_make();
    });

    after_each([&]() {
        ts_document_free(doc);
    });

    auto run_tests_for_language = [&](string language, TSParser (parser_constructor)()) {
        describe(language.c_str(), [&]() {
            before_each([&]() {
                ts_document_set_parser(doc, parser_constructor());
            });

            for (auto &entry : test_entries_for_language(language)) {
                it(entry.description.c_str(), [&]() {
                    ts_document_set_input_string(doc, entry.input.c_str());
                    auto doc_string = ts_document_string(doc);
                    AssertThat(doc_string, Equals(entry.tree_string.c_str()));
                    free((void *)doc_string);
                });
            }
        });
    };

    run_tests_for_language("json", ts_parser_json);
    run_tests_for_language("arithmetic", ts_parser_arithmetic);
    run_tests_for_language("javascript", ts_parser_javascript);
    run_tests_for_language("golang", ts_parser_golang);
});

END_TEST
