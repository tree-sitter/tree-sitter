#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/spy_reader.h"

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

  describe("set_input", [&]() {
    SpyReader *reader;

    before_each([&]() {
      reader = new SpyReader("{ \"key\": [1, 2] }", 5);
    });

    after_each([&]() {
      delete reader;
    });

    describe("when the language is set", [&]() {
      before_each([&]() {
        ts_document_set_language(doc, ts_language_json());
      });

      it("parses the document", [&]() {
        SpyReader *reader = new SpyReader("{ \"key\": [1, 2] }", 5);
        ts_document_set_input(doc, reader->input);

        AssertThat(string(ts_node_string(ts_document_root_node(doc))), Equals(
            "(DOCUMENT (object (string) (array (number) (number))))"
        ));
      });

      it("reads the entire input", [&]() {
        SpyReader *reader = new SpyReader("{ \"key\": [1, 2] }", 5);
        ts_document_set_input(doc, reader->input);
        AssertThat(reader->strings_read, Equals(vector<string>({
            "{ \"key\": [1, 2] }"
        })));
      });
    });

    describe("when the language is not set", [&]() {
      it("does not try to parse the document", [&]() {
        ts_document_set_input(doc, reader->input);

        AssertThat(ts_document_root_node(doc), Equals<TSNode *>(nullptr));
      });
    });
  });

  describe("edit", [&]() {
    SpyReader *reader;

    before_each([&]() {
      reader = new SpyReader("{ \"key\": [1, 2] }", 5);
      ts_document_set_language(doc, ts_language_json());
      ts_document_set_input(doc, reader->input);
    });

    after_each([&]() {
      delete reader;
    });

    describe("modifying the end of the input", [&]() {
      before_each([&]() {
        size_t position(string("{ \"key\": [1, 2]").length());
        string inserted_text(", \"key2\": 4");

        reader->content.insert(position, inserted_text);
        ts_document_edit(doc, { position, 0, inserted_text.length() });
      });

      it("updates the parse tree", [&]() {
        AssertThat(string(ts_node_string(ts_document_root_node(doc))), Equals(
            "(DOCUMENT (object (string) (array (number) (number)) (string) (number)))"));
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
        AssertThat(string(ts_node_string(ts_document_root_node(doc))), Equals(
            "(DOCUMENT (object (string) (number) (string) (array (number) (number))))"));
      });

      it_skip("re-reads only the changed portion of the input", [&]() {
        AssertThat(reader->strings_read.size(), Equals<size_t>(2));
        AssertThat(reader->strings_read[1], Equals("\"key2\": 4, "));
      });
    });
  });

  describe("parsing", [&]() {
    TSNode *root;

    describe("error handling", [&]() {
      before_each([&]() {
        ts_document_set_language(doc, ts_language_json());
      });

      describe("when the error occurs at the beginning of a token", [&]() {
        it("computes the error node's size and position correctly", [&]() {
          ts_document_set_input_string(doc, "  [123, @@@@@, true]");
          AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
              "(DOCUMENT (array (number) (ERROR '@') (true)))"));

          root = ts_document_root_node(doc);
          TSNode *array = ts_node_child(root, 0);
          TSNode *error = ts_node_child(array, 1);

          AssertThat(ts_node_name(error), Equals("error"));
          AssertThat(ts_node_pos(error), Equals(string("  [123,").length()))
          AssertThat(ts_node_size(error), Equals(string(" @@@@@").length()))

          ts_node_release(error);
          ts_node_release(array);
          ts_node_release(error);
        });
      });

      describe("when the error occurs in the middle of a token", [&]() {
        it("computes the error node's size and position correctly", [&]() {
          ts_document_set_input_string(doc, "  [123, total nonsense, true]");
          AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
              "(DOCUMENT (array (number) (ERROR 'o') (true)))"));

          root = ts_document_root_node(doc);
          TSNode *array = ts_node_child(root, 0);
          TSNode *error = ts_node_child(array, 1);

          AssertThat(ts_node_name(error), Equals("error"));
          AssertThat(ts_node_pos(error), Equals(string("  [123,").length()))
          AssertThat(ts_node_size(error), Equals(string(" total nonsense").length()))

          ts_node_release(error);
          ts_node_release(array);
          ts_node_release(error);
        });
      });

      describe("when the error occurs after one or more tokens", [&]() {
        it("computes the error node's size and position correctly", [&]() {
          ts_document_set_input_string(doc, "  [123, true false, true]");
          AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
              "(DOCUMENT (array (number) (ERROR 'f') (true)))"));

          root = ts_document_root_node(doc);
          TSNode *array = ts_node_child(root, 0);
          TSNode *error = ts_node_child(array, 1);

          AssertThat(ts_node_name(error), Equals("error"));
          AssertThat(ts_node_pos(error), Equals(string("  [123,").length()))
          AssertThat(ts_node_size(error), Equals(string(" true false").length()))

          ts_node_release(error);
          ts_node_release(array);
          ts_node_release(error);
        });
      });
    });
  });
});

END_TEST
