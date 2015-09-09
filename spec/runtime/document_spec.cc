#include "runtime/debugger.h"
#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/spy_debugger.h"
#include "runtime/helpers/spy_input.h"

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

        AssertThat(ts_node_string(ts_document_root_node(doc), doc), Equals(
          "(object (string) (array (number) (number)))"));
      });
    });

    describe("when the language is not set", [&]() {
      it("does not try to parse the document", [&]() {
        ts_document_set_input_string(doc, "{ \"key\": [1, 2] }");

        AssertThat(ts_document_root_node(doc).data, Equals<void *>(nullptr));
      });
    });

    it("allows the input to be retrieved later", [&]() {
      auto spy_input = new SpyInput("12345", 3);
      ts_document_set_input(doc, spy_input->input());
      AssertThat(ts_document_input(doc).payload, Equals<void *>(spy_input));
      delete spy_input;
    });
  });

  describe("set_language(TSLanguage)", [&]() {
    describe("when the input is not set", [&]() {
      it("does not try to parse the document", [&]() {
        ts_document_set_language(doc, ts_language_json());

        AssertThat(ts_document_root_node(doc).data, Equals<void *>(nullptr));
      });
    });

    describe("when the input is set", [&]() {
      before_each([&]() {
        ts_document_set_input_string(doc, "{ \"key\": [1, 2] }");
      });

      it("parses the document", [&]() {
        ts_document_set_language(doc, ts_language_json());

        AssertThat(ts_node_string(ts_document_root_node(doc), doc), Equals(
          "(object (string) (array (number) (number)))"));
      });
    });

    it("allows the language to be retrieved later", [&]() {
      ts_document_set_language(doc, ts_language_json());
      AssertThat(ts_document_language(doc), Equals(ts_language_json()));
    });
  });

  describe("set_debugger(TSDebugger)", [&]() {
    SpyDebugger *debugger;

    before_each([&]() {
      debugger = new SpyDebugger();
      ts_document_set_language(doc, ts_language_json());
      ts_document_set_debugger(doc, debugger->debugger());
    });

    it("calls the debugger with a message for each lex action", [&]() {
      ts_document_set_input_string(doc, "[1, 2]");

      AssertThat(debugger->messages, Contains("lookahead char:'1'"));
      AssertThat(debugger->messages, Contains("advance state:1"));
      AssertThat(debugger->messages, Contains("accept_token sym:number"));
    });

    it("calls the debugger with a message for each parse action", [&]() {
      ts_document_set_input_string(doc, "[1, 2]");

      AssertThat(debugger->messages, Contains("new_parse"));
      AssertThat(debugger->messages, Contains("lookahead char:'['"));
      AssertThat(debugger->messages, Contains("reduce sym:array, count:4"));
      AssertThat(debugger->messages, Contains("accept"));
    });

    it("allows the debugger to be retrieved later", [&]() {
      AssertThat(ts_document_debugger(doc).payload, Equals(debugger));
    });

    describe("disabling debugging", [&]() {
      before_each([&]() {
        ts_document_set_debugger(doc, ts_debugger_null());
      });

      it("does not call the debugger any more", [&]() {
        ts_document_set_input_string(doc, "[1, 2]");
        AssertThat(debugger->messages, IsEmpty());
      });
    });
  });
});

END_TEST
