#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/spy_debugger.h"

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

  describe("debugging", [&]() {
    SpyDebugger *debugger;

    before_each([&]() {
      ts_document_set_language(doc, ts_language_json());
      debugger = new SpyDebugger();
    });

    describe("debug_lex(TSDebugger)", [&]() {
      before_each([&]() {
        ts_document_debug_lex(doc, debugger->debugger());
      });

      it("calls the debugger with a message for each lex action", [&]() {
        ts_document_set_input_string(doc, "[1, 2]");

        AssertThat(debugger->messages, Contains("lookahead char:'1'"));
        AssertThat(debugger->messages, Contains("accept_token sym:number"));
        AssertThat(debugger->messages, Contains("advance state:1"));
      });

      describe("disabling debugging", [&]() {
        before_each([&]() {
          ts_document_debug_lex(doc, {});
        });

        it("does not call the debugger any more", [&]() {
          ts_document_set_input_string(doc, "[1, 2]");
          AssertThat(debugger->messages, IsEmpty());
        });

        it("releases the old debugger", [&]() {
          AssertThat(debugger->release_call_count, Equals<size_t>(1));
        });
      });
    });

    describe("debug_parse(TSDebugger)", [&]() {
      before_each([&]() {
        ts_document_debug_parse(doc, debugger->debugger());
      });

      it("calls the debugger with a message for each parse action", [&]() {
        ts_document_set_input_string(doc, "[1, 2]");

        AssertThat(debugger->messages, Contains("lex sym:number"));
        AssertThat(debugger->messages, Contains("shift state:1"));
        AssertThat(debugger->messages, Contains("reduce sym:value count:1"));
      });

      describe("disabling debugging", [&]() {
        before_each([&]() {
          ts_document_debug_parse(doc, {});
        });

        it("does not call the debugger any more", [&]() {
          ts_document_set_input_string(doc, "[1, 2]");
          AssertThat(debugger->messages, IsEmpty());
        });

        it("releases the old debugger", [&]() {
          AssertThat(debugger->release_call_count, Equals<size_t>(1));
        });
      });
    });
  });
});

END_TEST
