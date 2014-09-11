#include "runtime/runtime_spec_helper.h"

extern "C" const TSLanguage * ts_language_json();

START_TEST

describe("Document", [&]() {
  TSDocument *doc;

  before_each([&]() {
    doc = ts_document_make();
  });

  after_each([&]() {
    ts_document_free(doc);
  });

  describe("set_input(TSInput)", [&]() {
    describe("when the language is set", [&]() {
      before_each([&]() {
        ts_document_set_language(doc, ts_language_json());
      });

      it("parses the document", [&]() {
        ts_document_set_input_string(doc, "{ \"key\": [1, 2] }");

        AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
            "(DOCUMENT (object (string) (array (number) (number))))"));
      });
    });

    describe("when the language is not set", [&]() {
      it("does not try to parse the document", [&]() {
        ts_document_set_input_string(doc, "{ \"key\": [1, 2] }");

        AssertThat(ts_document_root_node(doc), Equals<TSNode *>(nullptr));
      });
    });
  });

  describe("set_language(TSLanguage)", [&]() {
    describe("when the input is not set", [&]() {
      it("does not try to parse the document", [&]() {
        ts_document_set_language(doc, ts_language_json());

        AssertThat(ts_document_root_node(doc), Equals<TSNode *>(nullptr));
      });
    });

    describe("when the input is set", [&]() {
      before_each([&]() {
        ts_document_set_input_string(doc, "{ \"key\": [1, 2] }");
      });

      it("parses the document", [&]() {
        ts_document_set_language(doc, ts_language_json());

        AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
            "(DOCUMENT (object (string) (array (number) (number))))"));
      });
    });
  });
});

END_TEST
