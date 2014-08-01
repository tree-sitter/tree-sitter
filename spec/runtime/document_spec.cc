#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/spy_reader.h"
#include "runtime/tree.h"

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

  describe("when the language is not set", [&]() {
    describe("setting the input", [&]() {
      SpyReader *reader;

      before_each([&]() {
        reader = new SpyReader("{ \"key\": [1, 2] }", 5);
        ts_document_set_input(doc, reader->input);
      });

      after_each([&]() {
        delete reader;
      });

      it("does not try to parse the document", [&]() {
        AssertThat(ts_document_root_node(doc), Equals<TSNode *>(nullptr));
      });

      describe("setting the language", [&]() {
        before_each([&]() {
          ts_document_set_language(doc, ts_language_json());
        });

        it("parses the document", [&]() {
          TSNode *node = ts_document_root_node(doc);
          AssertThat(string(ts_node_string(node)), Equals(
              "(object (string) (array (number) (number)))"));
          ts_node_release(node);
        });
      });
    });
  });

  describe("setting the language and input", [&]() {
    SpyReader *reader;

    before_each([&]() {
      reader = new SpyReader("{ \"key\": [1, 2] }", 5);
      ts_document_set_language(doc, ts_language_json());
      ts_document_set_input(doc, reader->input);
    });

    after_each([&]() {
      delete reader;
    });

    it("parses the input", [&]() {
      AssertThat(string(ts_document_string(doc)), Equals(
          "(object (string) (array (number) (number)))"));
    });

    it("reads the entire input", [&]() {
      AssertThat(reader->strings_read, Equals(vector<string>({
          "{ \"key\": [1, 2] }"
      })));
    });

    describe("modifying the end of the input", [&]() {
      before_each([&]() {
        size_t position(string("{ \"key\": [1, 2]").length());
        string inserted_text(", \"key2\": 4");

        reader->content.insert(position, inserted_text);
        ts_document_edit(doc, { position, 0, inserted_text.length() });
      });

      it("updates the parse tree", [&]() {
        AssertThat(string(ts_document_string(doc)), Equals(
            "(object (string) (array (number) (number)) (string) (number))"));
      });

      it("re-reads only the changed portion of the input", [&]() {
        AssertThat(reader->strings_read.size(), Equals<size_t>(2));
        AssertThat(reader->strings_read[1], Equals(", \"key2\": 4 }"));
      });
    });

    describe("modifying the beginning of the input", [&]() {
      before_each([&]() {
        size_t position(string("{ ").length());
        string inserted_text("\"key2\": 4, ");

        reader->content.insert(position, inserted_text);
        ts_document_edit(doc, { position, 0, inserted_text.length() });
      });

      it("updates the parse tree", [&]() {
        AssertThat(string(ts_document_string(doc)), Equals(
            "(object (string) (number) (string) (array (number) (number)))"));
      });

      it_skip("re-reads only the changed portion of the input", [&]() {
        AssertThat(reader->strings_read.size(), Equals<size_t>(2));
        AssertThat(reader->strings_read[1], Equals("\"key2\": 4, "));
      });
    });
  });
});

END_TEST
