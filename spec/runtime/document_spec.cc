#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/spy_reader.h"

extern "C" const TSLanguage * ts_language_json();
extern "C" const TSLanguage * ts_language_javascript();

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
      reader = new SpyReader("{ \"key\": [1, 2] }", 3);
      ts_document_set_language(doc, ts_language_json());
      ts_document_set_input(doc, reader->input);
      reader->clear();

      AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
          "(DOCUMENT (object (string) (array (number) (number))))"));
    });

    after_each([&]() {
      delete reader;
    });

    auto insert_text = [&](size_t position, string text) {
      reader->content.insert(position, text);
      ts_document_edit(doc, { position, 0, text.length() });
    };

    auto delete_text = [&](size_t position, size_t length) {
      reader->content.erase(position, length);
      ts_document_edit(doc, { position, length, 0 });
    };

    describe("inserting new tokens near the end of the input", [&]() {
      before_each([&]() {
        insert_text(
            strlen("{ \"key\": [1, 2]"),
            ", \"key2\": 4");
      });

      it("updates the parse tree", [&]() {
        AssertThat(string(ts_node_string(ts_document_root_node(doc))), Equals(
            "(DOCUMENT (object (string) (array (number) (number)) (string) (number)))"));
      });

      it("re-reads only the changed portion of the input", [&]() {
        AssertThat(reader->strings_read, Equals(vector<string>({ "], \"key2\": 4 }" })));
      });
    });

    describe("inserting text into the middle of an existing token", [&]() {
      it("updates the parse three", [&]() {
        insert_text(strlen("{ \"key"), "123");

        AssertThat(string(ts_node_string(ts_document_root_node(doc))), Equals(
            "(DOCUMENT (object (string) (array (number) (number))))"));
        TSNode *node = ts_node_find_for_pos(ts_document_root_node(doc), 3);
        AssertThat(ts_node_name(node), Equals("string"));
        AssertThat(ts_node_size(node), Equals(strlen("\"key123\"")));
        ts_node_release(node);
      });
    });

    describe("appending text to the end of an existing token", [&]() {
      it("updates the parse three", [&]() {
        insert_text(strlen("{ \"key\": [1"), "001");

        AssertThat(string(ts_node_string(ts_document_root_node(doc))), Equals(
            "(DOCUMENT (object (string) (array (number) (number))))"));

        TSNode *node = ts_node_find_for_pos(ts_document_root_node(doc), strlen("{ \"key\": ["));
        AssertThat(ts_node_name(node), Equals("number"));
        AssertThat(ts_node_size(node), Equals(strlen("1001")));
        ts_node_release(node);
      });
    });

    describe("deleting an important part of a token", [&]() {
      it("updates the parse tree, creating an error", [&]() {
        delete_text(strlen("{ \"key"), 1);

        AssertThat(string(ts_node_string(ts_document_root_node(doc))), Equals(
            "(DOCUMENT (end))"));
      });
    });

    describe("inserting tokens near the beginning of the input", [&]() {
      before_each([&]() {
        insert_text(
            strlen("{ "),
            "\"key2\": 4, ");
      });

      it("updates the parse tree", [&]() {
        AssertThat(string(ts_node_string(ts_document_root_node(doc))), Equals(
            "(DOCUMENT (object (string) (number) (string) (array (number) (number))))"));
      });

      it_skip("re-reads only the changed portion of the input", [&]() {
        AssertThat(reader->strings_read, Equals(vector<string>({ "\"key2\": 4, " })));
      });
    });
  });

  describe("parsing", [&]() {
    TSNode *root;

    describe("handling errors", [&]() {
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
          TSNode *last = ts_node_child(array, 2);

          AssertThat(ts_node_name(error), Equals("error"));
          AssertThat(ts_node_pos(error), Equals(string("  [123, ").length()))
          AssertThat(ts_node_size(error), Equals(string("@@@@@").length()))

          AssertThat(ts_node_name(last), Equals("true"));
          AssertThat(ts_node_pos(last), Equals(string("  [123, @@@@@, ").length()))

          ts_node_release(last);
          ts_node_release(error);
          ts_node_release(array);
        });
      });

      describe("when the error occurs in the middle of a token", [&]() {
        it("computes the error node's size and position correctly", [&]() {
          ts_document_set_input_string(doc, "  [123, faaaaalse, true]");
          AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
              "(DOCUMENT (array (number) (ERROR 'a') (true)))"));

          root = ts_document_root_node(doc);
          TSNode *array = ts_node_child(root, 0);
          TSNode *error = ts_node_child(array, 1);
          TSNode *last = ts_node_child(array, 2);

          AssertThat(ts_node_name(error), Equals("error"));
          AssertThat(ts_node_pos(error), Equals(string("  [123, ").length()))
          AssertThat(ts_node_size(error), Equals(string("faaaaalse").length()))

          AssertThat(ts_node_name(last), Equals("true"));
          AssertThat(ts_node_pos(last), Equals(string("  [123, faaaaalse, ").length()))

          ts_node_release(last);
          ts_node_release(error);
          ts_node_release(array);
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
          TSNode *last = ts_node_child(array, 2);

          AssertThat(ts_node_name(error), Equals("error"));
          AssertThat(ts_node_pos(error), Equals(string("  [123, ").length()))
          AssertThat(ts_node_size(error), Equals(string("true false").length()))

          AssertThat(ts_node_name(last), Equals("true"));
          AssertThat(ts_node_pos(last), Equals(string("  [123, true false, ").length()))

          ts_node_release(last);
          ts_node_release(error);
          ts_node_release(array);
        });
      });

      describe("when the error is an empty string", [&]() {
        it("computes the error node's size and position correctly", [&]() {
          ts_document_set_input_string(doc, "  [123, , true]");
          AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
              "(DOCUMENT (array (number) (ERROR ',') (true)))"));

          root = ts_document_root_node(doc);
          TSNode *array = ts_node_child(root, 0);
          TSNode *error = ts_node_child(array, 1);
          TSNode *last = ts_node_child(array, 2);

          AssertThat(ts_node_name(error), Equals("error"));
          AssertThat(ts_node_pos(error), Equals(string("  [123, ").length()))
          AssertThat(ts_node_size(error), Equals<size_t>(0))

          AssertThat(ts_node_name(last), Equals("true"));
          AssertThat(ts_node_pos(last), Equals(string("  [123, , ").length()))

          ts_node_release(last);
          ts_node_release(error);
          ts_node_release(array);
        });
      });
    });

    describe("handling ubiquitous tokens", [&]() {

      // In the javascript example grammar, ASI works by using newlines as
      // terminators in statements, but also as ubiquitous tokens.
      before_each([&]() {
        ts_document_set_language(doc, ts_language_javascript());
      });

      describe("when the token appears as part of a grammar rule", [&]() {
        it("is incorporated into the tree", [&]() {
          ts_document_set_input_string(doc, "fn()\n");
          AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
              "(DOCUMENT (program (expression_statement (function_call (identifier)))))"));
        });
      });

      describe("when the token appears somewhere else", [&]() {
        it("is incorporated into the tree", [&]() {
          ts_document_set_input_string(doc,
            "fn()\n"
            "  .otherFn();");
          AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
              "(DOCUMENT (program "
                "(expression_statement (function_call "
                  "(property_access (function_call (identifier)) (identifier))))))"));
        });

        describe("when several ubiquitous tokens appear in a row", [&]() {
          it("is incorporated into the tree", [&]() {
            ts_document_set_input_string(doc,
              "fn()\n\n"
              "// This is a comment"
              "\n\n"
              ".otherFn();");
            AssertThat(ts_node_string(ts_document_root_node(doc)), Equals(
                "(DOCUMENT (program "
                  "(expression_statement (function_call "
                    "(property_access (function_call (identifier)) "
                      "(comment) "
                      "(identifier))))))"));
          });
        });
      });
    });
  });
});

END_TEST
