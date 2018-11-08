#include "test_helper.h"
#include <future>
#include "runtime/alloc.h"
#include "runtime/language.h"
#include "runtime/get_changed_ranges.h"
#include "helpers/record_alloc.h"
#include "helpers/spy_input.h"
#include "helpers/load_language.h"
#include "helpers/record_alloc.h"
#include "helpers/point_helpers.h"
#include "helpers/spy_logger.h"
#include "helpers/stderr_logger.h"
#include "helpers/dedent.h"

START_TEST

describe("Parser", [&]() {
  TSParser *parser;
  TSTree *tree;
  SpyInput *input;
  TSNode root;
  size_t chunk_size;

  before_each([&]() {
    record_alloc::start();

    chunk_size = 3;
    input = nullptr;
    tree = nullptr;
    parser = ts_parser_new();
    if (getenv("TREE_SITTER_ENABLE_DEBUG_GRAPHS")) {
      ts_parser_print_dot_graphs(parser, stderr);
    }
  });

  after_each([&]() {
    if (parser) ts_parser_delete(parser);
    if (tree) ts_tree_delete(tree);
    if (input) delete input;

    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  auto set_text = [&](string text) {
    input = new SpyInput(text, chunk_size);
    tree = ts_parser_parse(parser, nullptr, input->input());
    root = ts_tree_root_node(tree);
    AssertThat(ts_node_end_byte(root), Equals(text.size()));
    input->clear();
  };

  auto replace_text = [&](size_t position, size_t length, string new_text) {
    size_t prev_size = ts_node_end_byte(root);

    TSInputEdit edit = input->replace(position, length, new_text);
    ts_tree_edit(tree, &edit);
    TSTree *new_tree = ts_parser_parse(parser, tree, input->input());
    ts_tree_delete(tree);
    tree = new_tree;

    root = ts_tree_root_node(tree);
    size_t new_size = ts_node_end_byte(root);
    AssertThat(new_size, Equals(prev_size - length + new_text.size()));
  };

  auto insert_text = [&](size_t position, string text) {
    replace_text(position, 0, text);
  };

  auto delete_text = [&](size_t position, size_t length) {
    replace_text(position, length, "");
  };

  auto undo = [&]() {
    TSInputEdit edit = input->undo();
    ts_tree_edit(tree, &edit);
    TSTree *new_tree = ts_parser_parse(parser, tree, input->input());
    ts_tree_delete(tree);
    tree = new_tree;
  };

  auto assert_root_node = [&](const string &expected) {
    TSNode node = ts_tree_root_node(tree);
    char *node_string = ts_node_string(node);
    string actual(node_string);
    ts_free(node_string);
    AssertThat(actual, Equals(expected));
  };

  auto get_node_text = [&](TSNode node) {
    size_t start = ts_node_start_byte(node);
    size_t end = ts_node_end_byte(node);
    return input->content.substr(start, end - start);
  };

  describe("handling errors", [&]() {
    describe("when there is an invalid substring right before a valid token", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        ts_parser_set_language(parser, load_real_language("json"));
        set_text("  [123,  @@@@@,   true]");
        assert_root_node("(value (array (number) (ERROR (UNEXPECTED '@')) (true)))");

        TSNode error = ts_node_named_child(ts_node_child(root, 0), 1);
        AssertThat(ts_node_type(error), Equals("ERROR"));
        AssertThat(get_node_text(error), Equals("@@@@@,"));
        AssertThat(ts_node_child_count(error), Equals<size_t>(2));

        TSNode garbage = ts_node_child(error, 0);
        AssertThat(get_node_text(garbage), Equals("@@@@@"));

        TSNode comma = ts_node_child(error, 1);
        AssertThat(get_node_text(comma), Equals(","));

        TSNode node_after_error = ts_node_next_named_sibling(error);
        AssertThat(ts_node_type(node_after_error), Equals("true"));
        AssertThat(get_node_text(node_after_error), Equals("true"));
      });
    });

    describe("when there is an unexpected string in the middle of a token", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        ts_parser_set_language(parser, load_real_language("json"));
        set_text("  [123, faaaaalse, true]");

        assert_root_node(
          "(value (array (number) (ERROR (UNEXPECTED 'a')) (true)))");

        TSNode error = ts_node_named_child(ts_node_child(root, 0), 1);
        AssertThat(ts_node_type(error), Equals("ERROR"));
        AssertThat(get_node_text(error), Equals("faaaaalse,"));
        AssertThat(ts_node_child_count(error), Equals<size_t>(2));

        TSNode garbage = ts_node_child(error, 0);
        AssertThat(ts_node_type(garbage), Equals("ERROR"));
        AssertThat(get_node_text(garbage), Equals("faaaaalse"));

        TSNode comma = ts_node_child(error, 1);
        AssertThat(ts_node_type(comma), Equals(","));
        AssertThat(get_node_text(comma), Equals(","));

        TSNode last = ts_node_next_named_sibling(error);
        AssertThat(ts_node_type(last), Equals("true"));
        AssertThat(ts_node_start_byte(last), Equals(strlen("  [123, faaaaalse, ")));
      });
    });

    describe("when there is one unexpected token between two valid tokens", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        ts_parser_set_language(parser, load_real_language("json"));
        set_text("  [123, true false, true]");

        assert_root_node("(value (array (number) (true) (ERROR (false)) (true)))");

        TSNode error = ts_node_named_child(ts_node_child(root, 0), 2);
        AssertThat(ts_node_type(error), Equals("ERROR"));
        AssertThat(get_node_text(error), Equals("false"));
        AssertThat(ts_node_child_count(error), Equals<size_t>(1));

        TSNode last = ts_node_next_named_sibling(error);
        AssertThat(ts_node_type(last), Equals("true"));
        AssertThat(get_node_text(last), Equals("true"));
      });
    });

    describe("when there is an unexpected string at the end of a token", [&]() {
      it("computes the error's size and position correctly", [&]() {
        ts_parser_set_language(parser, load_real_language("json"));
        set_text("  [123, \"hi\n, true]");
        assert_root_node("(value (array (number) (ERROR (UNEXPECTED '\\n')) (true)))");
      });
    });

    describe("when there is an unterminated error", [&]() {
      it("maintains a consistent tree", [&]() {
        ts_parser_set_language(parser, load_real_language("json"));
        set_text("nul");
        assert_root_node("(ERROR (UNEXPECTED EOF))");
      });
    });

    describe("when there are extra tokens at the end of the viable prefix", [&]() {
      it("does not include them in the error node", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text(
          "var x;\n"
          "\n"
          "if\n"
          "\n"
          "var y;"
        );

        TSNode error = ts_node_named_child(root, 1);
        AssertThat(ts_node_type(error), Equals("ERROR"));
        AssertThat(ts_node_start_point(error), Equals<TSPoint>({2, 0}));
        AssertThat(ts_node_end_point(error), Equals<TSPoint>({2, 2}));
      });
    });

    it("handles invalid UTF8 characters at EOF", [&]() {
      char *string = (char *)malloc(1);
      string[0] = '\xdf';

      ts_parser_set_language(parser, load_real_language("json"));
      tree = ts_parser_parse_string(parser, nullptr, string, 1);

      free(string);
      assert_root_node("(ERROR (UNEXPECTED INVALID))");
    });

    describe("when halt_on_error is set to true", [&]() {
      it("halts as soon as an error is found if the halt_on_error flag is set", [&]() {
        string input_string = "[1, null, error, 3]";
        ts_parser_set_language(parser, load_real_language("json"));

        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(value (array (number) (null) (ERROR (UNEXPECTED 'e')) (number)))");

        ts_parser_halt_on_error(parser, true);

        ts_tree_delete(tree);
        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(ERROR (number) (null))");
        AssertThat(ts_node_end_byte(root), Equals(input_string.size()));
      });

      it("does not insert missing tokens if the halt_on_error flag is set", [&]() {
        string input_string = "[1, null, 3";
        ts_parser_set_language(parser, load_real_language("json"));

        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(value (array (number) (null) (number) (MISSING)))");

        ts_parser_halt_on_error(parser, true);

        ts_tree_delete(tree);
        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(ERROR (number) (null) (number))");
        AssertThat(ts_node_end_byte(root), Equals(input_string.size()));
      });

      it("can parse valid code with the halt_on_error flag set", [&]() {
        string input_string = "[1, null, 3]";
        ts_parser_set_language(parser, load_real_language("json"));

        ts_parser_halt_on_error(parser, true);
        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(value (array (number) (null) (number)))");
      });
    });
  });

  describe("editing", [&]() {
    describe("creating new tokens near the end of the input", [&]() {
      it("updates the parse tree and re-reads only the changed portion of the text", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("x * (100 + abc);");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(identifier) "
            "(parenthesized_expression "
              "(binary_expression (number) (identifier))))))");

        insert_text(strlen("x * (100 + abc"), ".d");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(identifier) "
            "(parenthesized_expression "
              "(binary_expression (number) (member_expression (identifier) (property_identifier)))))))");

        AssertThat(input->strings_read(), Equals(vector<string>({
          // The '*' is not reused because the preceding `x` expression is reused, which
          // puts the parser into a different state than when the `*` was initially tokenized.
          // When the `*` was initially tokenized, `x` was just an identifier. In both of these
          // states, external tokens are valid so we don't reuse tokens unless the lex states
          // match. This could probably be improved somehow.
          " * ",
          " abc.d)"
        })));
      });
    });

    describe("creating new tokens near the beginning of the input", [&]() {
      it("updates the parse tree and re-reads only the changed portion of the input", [&]() {
        chunk_size = 2;

        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("123 + 456 * (10 + x);");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(number) "
            "(binary_expression (number) (parenthesized_expression (binary_expression (number) (identifier)))))))");

        insert_text(strlen("123"), " || 5");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(number) "
            "(binary_expression "
              "(number) "
              "(binary_expression (number) (parenthesized_expression (binary_expression (number) (identifier))))))))");

        AssertThat(input->strings_read(), Equals(vector<string>({
          "123 || 5 ",
          ";"
        })));
      });
    });

    describe("introducing an error", [&]() {
      it("gives the error the right size", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("var x = y;");

        assert_root_node(
          "(program (variable_declaration (variable_declarator "
            "(identifier) (identifier))))");

        insert_text(strlen("var x = y"), " *");

        assert_root_node(
          "(program (variable_declaration (variable_declarator "
            "(identifier) (identifier)) (ERROR)))");

        insert_text(strlen("var x = y *"), " z");

        assert_root_node(
          "(program (variable_declaration (variable_declarator "
            "(identifier) (binary_expression (identifier) (identifier)))))");
      });
    });

    describe("into the middle of an existing token", [&]() {
      it("updates the parse tree", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("abc * 123;");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        insert_text(strlen("ab"), "XYZ");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        TSNode node = ts_node_named_descendant_for_byte_range(root, 1, 1);
        AssertThat(ts_node_type(node), Equals("identifier"));
        AssertThat(ts_node_end_byte(node), Equals(strlen("abXYZc")));
      });
    });

    describe("at the end of an existing token", [&]() {
      it("updates the parse tree", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("abc * 123;");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        insert_text(strlen("abc"), "XYZ");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        TSNode node = ts_node_named_descendant_for_byte_range(root, 1, 1);
        AssertThat(ts_node_type(node), Equals("identifier"));
        AssertThat(ts_node_end_byte(node), Equals(strlen("abcXYZ")));
      });
    });

    describe("inserting text into a node containing a extra token", [&]() {
      it("updates the parse tree", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("123 *\n"
          "// a-comment\n"
          "abc;");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(number) "
            "(comment) "
            "(identifier))))");

        insert_text(
          strlen("123 *\n"
            "// a-comment\n"
            "abc"),
          "XYZ");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(number) "
            "(comment) "
            "(identifier))))");
      });
    });

    describe("when a critical token is removed", [&]() {
      it("updates the parse tree, creating an error", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("123 * 456; 789 * 123;");

        assert_root_node(
          "(program "
            "(expression_statement (binary_expression (number) (number))) "
            "(expression_statement (binary_expression (number) (number))))");

        delete_text(strlen("123 "), 2);

        assert_root_node(
          "(program "
            "(ERROR (number)) "
            "(expression_statement (number)) "
            "(expression_statement (binary_expression (number) (number))))");
      });
    });

    describe("with external tokens", [&]() {
      it("maintains the external scanner's state during incremental parsing", [&]() {
        ts_parser_set_language(parser, load_real_language("python"));
        string text = dedent(R"PYTHON(
          if a:
              print b
          return c
        )PYTHON");

        set_text(text);
        assert_root_node("(module "
          "(if_statement (identifier) "
            "(print_statement (identifier))) "
          "(return_statement (expression_list (identifier))))");

        replace_text(text.find("return"), 0, "    ");
        assert_root_node("(module "
          "(if_statement (identifier) "
            "(print_statement (identifier)) "
            "(return_statement (expression_list (identifier)))))");

        undo();
        assert_root_node("(module "
          "(if_statement (identifier) "
            "(print_statement (identifier))) "
          "(return_statement (expression_list (identifier))))");
      });
    });

    it("does not try to reuse nodes that are within the edited region", [&]() {
      ts_parser_set_language(parser, load_real_language("javascript"));
      set_text("{ x: (b.c) };");

      assert_root_node(
        "(program (expression_statement (object (pair "
          "(property_identifier) (parenthesized_expression (member_expression (identifier) (property_identifier)))))))");

      replace_text(strlen("{ x: "), strlen("(b.c)"), "b.c");

      assert_root_node(
        "(program (expression_statement (object (pair "
          "(property_identifier) (member_expression (identifier) (property_identifier))))))");
    });
  });

  describe("lexing", [&]() {
    describe("handling tokens containing wildcard patterns (e.g. comments)", [&]() {
      it("terminates them at the end of the string", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("x; // this is a comment");

        assert_root_node(
          "(program (expression_statement (identifier)) (comment))");

        TSNode comment = ts_node_named_child(root, 1);

        AssertThat(ts_node_start_byte(comment), Equals(strlen("x; ")));
        AssertThat(ts_node_end_byte(comment), Equals(strlen("x; // this is a comment")));
      });
    });

    it("recognizes UTF8 characters as single characters", [&]() {
      // 'ΩΩΩ — ΔΔ';
      ts_parser_set_language(parser, load_real_language("javascript"));
      set_text("'\u03A9\u03A9\u03A9 \u2014 \u0394\u0394';");

      assert_root_node(
        "(program (expression_statement (string)))");

      AssertThat(ts_node_end_byte(root), Equals(strlen("'\u03A9\u03A9\u03A9 \u2014 \u0394\u0394';")));
    });

    it("handles non-UTF8 characters", [&]() {
      const char *string = "cons\xeb\x00e=ls\x83l6hi');\x0a";

      ts_parser_set_language(parser, load_real_language("javascript"));
      tree = ts_parser_parse_string(parser, nullptr, string, strlen(string));
      TSNode root = ts_tree_root_node(tree);
      AssertThat(ts_node_end_byte(root), Equals(strlen(string)));
    });
  });

  describe("handling TSInputs", [&]() {
    SpyInput *spy_input;

    before_each([&]() {
      spy_input = new SpyInput("{\"key\": [null, 2]}", 3);
      ts_parser_set_language(parser, load_real_language("json"));
    });

    after_each([&]() {
      delete spy_input;
    });

    it("handles UTF16 encodings", [&]() {
      const char16_t content[] = u"[true, false]";
      spy_input->content = string((const char *)content, sizeof(content));
      spy_input->encoding = TSInputEncodingUTF16;

      tree = ts_parser_parse(parser, nullptr, spy_input->input());
      root = ts_tree_root_node(tree);
      assert_root_node(
        "(value (array (true) (false)))");
    });

    it("handles truncated UTF16 data", [&]() {
      const char content[1] = { '\0' };
      spy_input->content = string(content, sizeof(content));
      spy_input->encoding = TSInputEncodingUTF16;

      tree = ts_parser_parse(parser, nullptr, spy_input->input());
    });

    it("measures columns in bytes", [&]() {
      const char16_t content[] = u"[true, false]";
      spy_input->content = string((const char *)content, sizeof(content));
      spy_input->encoding = TSInputEncodingUTF16;

      tree = ts_parser_parse(parser, nullptr, spy_input->input());
      root = ts_tree_root_node(tree);
      AssertThat(ts_node_end_point(root), Equals<TSPoint>({0, 28}));
    });

    it("handles input chunks that end in the middle of multi-byte characters", [&]() {
      ts_parser_set_language(parser, load_real_language("c"));
      spy_input->content = "A b = {'👍','👍'};";
      spy_input->chars_per_chunk = 4;

      tree = ts_parser_parse(parser, nullptr, spy_input->input());
      root = ts_tree_root_node(tree);
      assert_root_node(
        "(translation_unit (declaration "
          "(type_identifier) "
          "(init_declarator "
            "(identifier) "
            "(initializer_list (char_literal) (char_literal)))))");
    });
  });

  describe("set_language(language)", [&]() {
    string input_string = "{\"key\": [1, 2]}\n";

    it("uses the given language for future parses", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));
      tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());

      root = ts_tree_root_node(tree);
      assert_root_node(
        "(value (object (pair (string) (array (number) (number)))))");
    });

    it("does not allow setting a language with a different version number", [&]() {
      TSLanguage language = *load_real_language("json");
      AssertThat(ts_language_version(&language), Equals<uint32_t>(TREE_SITTER_LANGUAGE_VERSION));

      language.version++;
      AssertThat(ts_language_version(&language), !Equals<uint32_t>(TREE_SITTER_LANGUAGE_VERSION));

      AssertThat(ts_parser_set_language(parser, &language), IsFalse());
      AssertThat(ts_parser_language(parser), Equals<const TSLanguage *>(nullptr));
    });

    it("does nothing when parse is called while the language is null", [&]() {
      tree = ts_parser_parse_string(parser, nullptr, "{}", 2);
      AssertThat(tree, Equals<TSTree *>(nullptr));

      ts_parser_set_language(parser, nullptr);
      tree = ts_parser_parse_string(parser, nullptr, "{}", 2);
      AssertThat(tree, Equals<TSTree *>(nullptr));
    });
  });

  describe("set_logger(TSLogger)", [&]() {
    SpyLogger *logger;

    before_each([&]() {
      logger = new SpyLogger();
      ts_parser_set_language(parser, load_real_language("json"));
    });

    after_each([&]() {
      delete logger;
    });

    it("calls the debugger with a message for each parse action", [&]() {
      ts_parser_set_logger(parser, logger->logger());
      tree = ts_parser_parse_string(parser, nullptr, "[ 1, 2, 3 ]", 11);

      AssertThat(logger->messages, Contains("new_parse"));
      AssertThat(logger->messages, Contains("skip character:' '"));
      AssertThat(logger->messages, Contains("consume character:'['"));
      AssertThat(logger->messages, Contains("consume character:'1'"));
      AssertThat(logger->messages, Contains("reduce sym:array, child_count:4"));
      AssertThat(logger->messages, Contains("accept"));
    });

    it("allows the debugger to be retrieved later", [&]() {
      ts_parser_set_logger(parser, logger->logger());
      AssertThat(ts_parser_logger(parser).payload, Equals(logger));
    });

    describe("disabling debugging", [&]() {
      before_each([&]() {
        ts_parser_set_logger(parser, logger->logger());
        ts_parser_set_logger(parser, {NULL, NULL});
      });

      it("does not call the debugger any more", [&]() {
        tree = ts_parser_parse_string(parser, nullptr, "{}", 2);
        AssertThat(logger->messages, IsEmpty());
      });
    });
  });

  describe("set_enabled(enabled)", [&]() {
    it("stops the in-progress parse if false is passed", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));
      AssertThat(ts_parser_enabled(parser), IsTrue());

      auto tree_future = std::async([parser]() {
        size_t read_count = 0;
        TSInput infinite_input = {
          &read_count,
          [](void *payload, uint32_t byte, TSPoint position, uint32_t *bytes_read) {
            size_t *read_count = static_cast<size_t *>(payload);
            assert((*read_count)++ < 100000);
            *bytes_read = 1;
            return "[";
          },
          TSInputEncodingUTF8
        };

        return ts_parser_parse(parser, nullptr, infinite_input);
      });

      auto cancel_future = std::async([parser]() {
        ts_parser_set_enabled(parser, false);
      });

      cancel_future.wait();
      tree_future.wait();
      AssertThat(ts_parser_enabled(parser), IsFalse());
      AssertThat(tree_future.get(), Equals<TSTree *>(nullptr));

      TSTree *tree = ts_parser_parse_string(parser, nullptr, "[]", 2);
      AssertThat(ts_parser_enabled(parser), IsFalse());
      AssertThat(tree, Equals<TSTree *>(nullptr));

      ts_parser_set_enabled(parser, true);
      AssertThat(ts_parser_enabled(parser), IsTrue());
      tree = ts_parser_parse_string(parser, nullptr, "[]", 2);
      AssertThat(tree, !Equals<TSTree *>(nullptr));
      ts_tree_delete(tree);
    });
  });

  describe("set_operation_limit(limit)", [&]() {
    it("limits the amount of work the parser does on any given call to parse()", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));

      struct InputState {
        const char *string;
        size_t read_count;
      };

      InputState state = {"[", 0};

      // An input that repeats the given string forever, counting how many times
      // it has been read.
      TSInput infinite_input = {
        &state,
        [](void *payload, uint32_t byte, TSPoint position, uint32_t *bytes_read) {
          InputState *state = static_cast<InputState *>(payload);
          assert(state->read_count++ <= 11);
          *bytes_read = strlen(state->string);
          return state->string;
        },
        TSInputEncodingUTF8
      };

      ts_parser_set_operation_limit(parser, 10);
      TSTree *tree = ts_parser_parse(parser, nullptr, infinite_input);
      AssertThat(tree, Equals<TSTree *>(nullptr));

      state.read_count = 0;
      state.string = "";

      tree = ts_parser_parse(parser, nullptr, infinite_input);
      AssertThat(tree, !Equals<TSTree *>(nullptr));
      ts_tree_delete(tree);
    });

    it("retains the old tree even if the parser halts before finishing parsing", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));

      SpyInput input("[1234, 5, 6, 4, 5]", 3);
      tree = ts_parser_parse(parser, nullptr, input.input());
      assert_root_node("(value (array (number) (number) (number) (number) (number)))");

      input.clear();
      TSInputEdit edit = input.replace(1, 4, "null");
      ts_tree_edit(tree, &edit);

      ts_parser_set_operation_limit(parser, 1);
      TSTree *new_tree = ts_parser_parse(parser, tree, input.input());
      AssertThat(new_tree, Equals<TSTree *>(nullptr));

      ts_tree_delete(tree);
      ts_parser_set_operation_limit(parser, SIZE_MAX);
      tree = ts_parser_parse(parser, nullptr, input.input());
      assert_root_node("(value (array (null) (number) (number) (number) (number)))");

      AssertThat(input.strings_read(), Equals(vector<string>({
        "[null,",
      })));
    });

    it("does not leak the old tree if parsing halts and never finishes", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));

      SpyInput input("[1234, 5, 6, 4, 5]", 3);
      tree = ts_parser_parse(parser, nullptr, input.input());
      assert_root_node("(value (array (number) (number) (number) (number) (number)))");

      input.clear();
      TSInputEdit edit = input.replace(1, 4, "null");
      ts_tree_edit(tree, &edit);

      ts_parser_set_operation_limit(parser, 1);
      TSTree *new_tree = ts_parser_parse(parser, tree, input.input());
      AssertThat(new_tree, Equals<TSTree *>(nullptr));
    });
  });

  describe("reset()", [&]() {
    it("causes the parser to parse from scratch on the next call to parse, instead of resuming", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));

      ts_parser_set_operation_limit(parser, 3);
      tree = ts_parser_parse_string(parser, nullptr, "[1234, 5, 6, 4, 5]", 18);
      AssertThat(tree, Equals<TSTree *>(nullptr));

      // Without calling reset, the parser continues from where it left off, so
      // it does not see the changes to the beginning of the source code.
      ts_parser_set_operation_limit(parser, SIZE_MAX);
      tree = ts_parser_parse_string(parser, nullptr, "[null, 5, 6, 4, 5]", 18);
      assert_root_node("(value (array (number) (number) (number) (number) (number)))");
      ts_tree_delete(tree);

      ts_parser_set_operation_limit(parser, 3);
      tree = ts_parser_parse_string(parser, nullptr, "[1234, 5, 6, 4, 5]", 18);
      AssertThat(tree, Equals<TSTree *>(nullptr));

      // By calling reset, we force the parser to start over from scratch so
      // that it sees the changes to the beginning of the source code.
      ts_parser_set_operation_limit(parser, SIZE_MAX);
      ts_parser_reset(parser);
      tree = ts_parser_parse_string(parser, nullptr, "[null, 5, 6, 4, 5]", 18);
      assert_root_node("(value (array (null) (number) (number) (number) (number)))");
    });
  });

  describe("set_included_ranges()", [&]() {
    it("can parse code within a single range of a document", [&]() {
      string source_code = "<span>hi</span><script>console.log('sup');</script>";

      ts_parser_set_language(parser, load_real_language("html"));
      TSTree *html_tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(), source_code.size());
      TSNode script_content_node = ts_node_child(
        ts_node_child(ts_tree_root_node(html_tree), 1),
        1
      );
      AssertThat(ts_node_type(script_content_node), Equals("raw_text"));
      TSRange included_range = {
        ts_node_start_point(script_content_node),
        ts_node_end_point(script_content_node),
        ts_node_start_byte(script_content_node),
        ts_node_end_byte(script_content_node),
      };
      ts_tree_delete(html_tree);

      ts_parser_set_included_ranges(parser, &included_range, 1);
      ts_parser_set_language(parser, load_real_language("javascript"));
      tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(), source_code.size());

      assert_root_node("(program (expression_statement (call_expression "
        "(member_expression (identifier) (property_identifier)) "
        "(arguments (string)))))");

      AssertThat(
        ts_node_start_point(ts_tree_root_node(tree)),
        Equals<TSPoint>({0, static_cast<uint32_t>(source_code.find("console"))})
      );
    });

    it("can parse code spread across multiple ranges in a document", [&]() {
      string source_code =
        "html `<div>Hello, ${name.toUpperCase()}, it's <b>${now()}</b>.</div>`";

      ts_parser_set_language(parser, load_real_language("javascript"));
      TSTree *js_tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(), source_code.size());
      TSNode root_node = ts_tree_root_node(js_tree);
      TSNode string_node = ts_node_descendant_for_byte_range(
        root_node,
        source_code.find("<div>"),
        source_code.find("Hell")
      );
      TSNode open_quote_node = ts_node_child(string_node, 0);
      TSNode interpolation_node1 = ts_node_child(string_node, 1);
      TSNode interpolation_node2 = ts_node_child(string_node, 2);
      TSNode close_quote_node = ts_node_child(string_node, 3);

      AssertThat(ts_node_type(string_node), Equals("template_string"));
      AssertThat(ts_node_type(open_quote_node), Equals("`"));
      AssertThat(ts_node_type(interpolation_node1), Equals("template_substitution"));
      AssertThat(ts_node_type(interpolation_node2), Equals("template_substitution"));
      AssertThat(ts_node_type(close_quote_node), Equals("`"));

      TSRange included_ranges[] = {
        {
          ts_node_end_point(open_quote_node),
          ts_node_start_point(interpolation_node1),
          ts_node_end_byte(open_quote_node),
          ts_node_start_byte(interpolation_node1),
        },
        {
          ts_node_end_point(interpolation_node1),
          ts_node_start_point(interpolation_node2),
          ts_node_end_byte(interpolation_node1),
          ts_node_start_byte(interpolation_node2),
        },
        {
          ts_node_end_point(interpolation_node2),
          ts_node_start_point(close_quote_node),
          ts_node_end_byte(interpolation_node2),
          ts_node_start_byte(close_quote_node),
        }
      };

      ts_parser_set_included_ranges(parser, included_ranges, 3);
      ts_tree_delete(js_tree);
      ts_parser_set_language(parser, load_real_language("html"));
      tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(), source_code.size());

      assert_root_node("(fragment "
        "(element "
          "(start_tag (tag_name)) "
          "(text) "
          "(element "
            "(start_tag (tag_name)) "
            "(end_tag (tag_name))) "
          "(text) "
          "(end_tag (tag_name))))");

      root_node = ts_tree_root_node(tree);
      TSNode div_element_node = ts_node_child(root_node, 0);

      TSNode hello_text_node = ts_node_child(div_element_node, 1);
      AssertThat(ts_node_type(hello_text_node), Equals("text"));
      AssertThat(
        ts_node_start_point(hello_text_node),
        Equals<TSPoint>({0, static_cast<uint32_t>(source_code.find("Hello"))})
      );
      AssertThat(
        ts_node_end_point(hello_text_node),
        Equals<TSPoint>({0, static_cast<uint32_t>(source_code.find("<b>"))})
      );

      TSNode b_start_tag_node = ts_node_child(ts_node_child(div_element_node, 2), 0);
      AssertThat(ts_node_type(b_start_tag_node), Equals("start_tag"));
      AssertThat(
        ts_node_start_point(b_start_tag_node),
        Equals<TSPoint>({0, static_cast<uint32_t>(source_code.find("<b>"))})
      );
      AssertThat(
        ts_node_end_point(b_start_tag_node),
        Equals<TSPoint>({0, static_cast<uint32_t>(source_code.find("${now()}"))})
      );

      TSNode b_end_tag_node = ts_node_child(ts_node_child(div_element_node, 2), 1);
      AssertThat(ts_node_type(b_end_tag_node), Equals("end_tag"));
      AssertThat(
        ts_node_start_point(b_end_tag_node),
        Equals<TSPoint>({0, static_cast<uint32_t>(source_code.find("</b>"))})
      );
      AssertThat(
        ts_node_end_point(b_end_tag_node),
        Equals<TSPoint>({0, static_cast<uint32_t>(source_code.find(".</div>"))})
      );
    });

    it("can handle errors at the ends of the nested UTF16 documents (regression)", [&]() {
      u16string source_code = u"<script>a.</script>";

      TSRange included_range = {
        {0, static_cast<uint32_t>(2u * source_code.find(u"a."))},
        {0, static_cast<uint32_t>(2u * source_code.find(u"</script"))},
        2u * static_cast<uint32_t>(source_code.find(u"a.")),
        2u * static_cast<uint32_t>(source_code.find(u"</script")),
      };

      ts_parser_set_included_ranges(parser, &included_range, 1);
      ts_parser_set_language(parser, load_real_language("javascript"));

      SpyInput input("", 3);
      input.content.assign((const char *)source_code.c_str(), source_code.size() * 2);
      input.encoding = TSInputEncodingUTF16;
      tree = ts_parser_parse(parser, nullptr, input.input());

      assert_root_node("(program (ERROR (identifier)))");
    });

    it("does not allow missing tokens to be inserted outside of included ranges", [&]() {
      string test_grammar = R"JSON({
        "name": "test_leading_missing_token",
        "rules": {
          "program": {
            "type": "SEQ",
            "members": [
              {"type": "SYMBOL", "name": "A"},
              {"type": "SYMBOL", "name": "b"},
              {"type": "SYMBOL", "name": "c"},
              {"type": "SYMBOL", "name": "A"},
              {"type": "SYMBOL", "name": "b"},
              {"type": "SYMBOL", "name": "c"}
            ]
          },
          "A": {"type": "SYMBOL", "name": "a"},
          "a": {"type": "STRING", "value": "a"},
          "b": {"type": "STRING", "value": "b"},
          "c": {"type": "STRING", "value": "c"}
        }
      })JSON";

      const TSLanguage *language = load_test_language(
        "test_leading_missing_token",
        ts_compile_grammar(test_grammar.c_str(), nullptr)
      );

      ts_parser_set_language(parser, language);

      // There's a missing `a` token at the beginning of the code. It must be inserted
      // at the beginning of the first included range, not at {0, 0}.
      string source_code = "__bc__bc__";
      TSRange included_ranges[2] = {
        {{0, 2}, {0, 4}, 2, 4},
        {{0, 6}, {0, 8}, 6, 8},
      };
      ts_parser_set_included_ranges(parser, included_ranges, 2);
      tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(), source_code.size());
      root = ts_tree_root_node(tree);


      assert_root_node("(program (A (MISSING)) (b) (c) (A (MISSING)) (b) (c))");
      AssertThat(ts_node_start_point(root), Equals<TSPoint>({0, 2}));
      AssertThat(ts_node_start_point(ts_node_child(root, 3)), Equals<TSPoint>({0, 4}));
    });

    it("allows external scanners to detect the boundaries of included ranges", [&]() {
      string source_code = "a <%= b() %> c <% d() %>";

      TSRange included_ranges[] = {
        range_for_substring(source_code, "b()"),
        range_for_substring(source_code, "d()"),
      };

      ts_parser_set_included_ranges(parser, included_ranges, 2);
      ts_parser_set_language(parser, load_real_language("javascript"));
      tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(), source_code.size());

      assert_root_node("(program "
        "(expression_statement (call_expression (identifier) (arguments))) "
        "(expression_statement (call_expression (identifier) (arguments))))");

      TSNode statement_node1 = ts_node_child(ts_tree_root_node(tree), 0);
      TSNode statement_node2 = ts_node_child(ts_tree_root_node(tree), 1);

      AssertThat(ts_node_end_point(statement_node1), Equals(extent_for_string("a <%= b()")));
      AssertThat(ts_node_end_point(statement_node2), Equals(extent_for_string("a <%= b() %> c <% d()")));
    });

    it("handles syntax changes in ranges that were included but are now excluded", [&]() {
      string source_code = "<div><span><%= something %></span></div>";

      // Parse HTML including the template directive, which will cause an error
      ts_parser_set_language(parser, load_real_language("html"));
      TSTree *first_tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(), source_code.size());

      // Insert code at the beginning of the document.
      string prefix = "a very very long line of plain text. ";
      unsigned prefix_length = prefix.size();
      TSInputEdit edit = {
        0, 0, prefix_length,
        {0, 0}, {0, 0}, {0, prefix_length}
      };
      ts_tree_edit(first_tree, &edit);
      source_code = prefix + source_code;

      // Parse the HTML again, this time *excluding* the template directive
      // (which has moved since the previous parse).
      unsigned directive_start = source_code.find("<%=");
      unsigned directive_end = source_code.find("</span>");
      unsigned source_code_end = source_code.size();

      TSRange included_ranges[] = {
        {
          {0, 0},
          {0, directive_start},
          0,
          directive_start
        },
        {
          {0, directive_end},
          {0, source_code_end},
          directive_end,
          source_code_end
        }
      };

      ts_parser_set_included_ranges(parser, included_ranges, 2);
      tree = ts_parser_parse_string(parser, first_tree, source_code.c_str(), source_code.size());

      // The element node (which contained an error) should not be reused,
      // because it contains a range which is now excluded.
      assert_root_node("(fragment "
        "(text) "
        "(element "
          "(start_tag (tag_name)) "
          "(element "
            "(start_tag (tag_name)) "
            "(end_tag (tag_name))) "
          "(end_tag (tag_name))))");

      unsigned range_count;
      const TSRange *ranges = ts_tree_get_changed_ranges(first_tree, tree, &range_count);

      // The first range that's changed syntax is the range of the
      // newly-inserted text.
      AssertThat(range_count, Equals(2u));
      AssertThat(ranges[0], Equals<TSRange>({
        {0, 0}, {0, prefix_length},
        0, prefix_length,
      }));

      // Even though no edits were applied to the outer `div` element,
      // its contents have changed syntax because a range of text that
      // was previously included is now excluded.
      AssertThat(ranges[1], Equals<TSRange>({
        {0, directive_start}, {0, directive_end},
        directive_start, directive_end,
      }));

      ts_free((void *)ranges);
      ts_tree_delete(first_tree);
    });

    it("handles syntax changes in ranges that were excluded but are now included", [&]() {
      ts_parser_set_language(parser, load_real_language("javascript"));

      string source_code = "<div><%= foo() %></div><div><%= bar() %>";

      unsigned first_code_start_index = source_code.find(" foo");
      unsigned first_code_end_index = first_code_start_index + 7;
      unsigned second_code_start_index = source_code.find(" bar");
      unsigned second_code_end_index = second_code_start_index + 7;

      TSRange included_ranges[] = {
        {
          {0, first_code_start_index},
          {0, first_code_end_index},
          first_code_start_index,
          first_code_end_index
        },
        {
          {0, second_code_start_index},
          {0, second_code_end_index},
          second_code_start_index,
          second_code_end_index
        },
      };

      // Parse only the first code directive as JavaScript
      ts_parser_set_included_ranges(parser, included_ranges, 1);
      TSTree *first_tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(), source_code.size());

      // Parse both the code directives as JavaScript, using the old tree as a reference.
      ts_parser_set_included_ranges(parser, included_ranges, 2);
      tree = ts_parser_parse_string(parser, first_tree, source_code.c_str(), source_code.size());

      assert_root_node("(program "
        "(expression_statement (call_expression (identifier) (arguments))) "
        "(expression_statement (call_expression (identifier) (arguments))))");

      unsigned range_count;
      const TSRange *ranges = ts_tree_get_changed_ranges(first_tree, tree, &range_count);
      AssertThat(range_count, Equals(1u));
      AssertThat(ranges[0], Equals<TSRange>({
        {0, first_code_end_index + 1}, {0, second_code_end_index + 1},
        first_code_end_index + 1, second_code_end_index + 1,
      }));

      ts_free((void *)ranges);
      ts_tree_delete(first_tree);
    });
  });

  describe("ts_range_array_get_changed_ranges()", [&]() {
    auto get_changed_ranges = [&](
      const vector<TSRange> &old_ranges,
      const vector<TSRange> &new_ranges
    ) {
      TSRangeArray result = array_new();
      ts_range_array_get_changed_ranges(
        old_ranges.data(), old_ranges.size(),
        new_ranges.data(), new_ranges.size(),
        &result
      );
      vector<TSRange> result_vector;
      for (unsigned i = 0; i < result.size; i++) {
        result_vector.push_back(result.contents[i]);
      }
      array_delete(&result);
      return result_vector;
    };

    auto range = [&](unsigned start, unsigned end) {
      TSRange result;
      result.start_byte = start;
      result.end_byte = end;
      result.start_point = {0, start};
      if (end == UINT32_MAX) {
        result.end_point = {UINT32_MAX, UINT32_MAX};
      } else {
        result.end_point = {0, end};
      }
      return result;
    };

    it("returns an array of ranges that are newly included excluded", [&]() {
      AssertThat(get_changed_ranges(
        {
          range(0, UINT32_MAX),
        },
        {
          range(0, 5),
          range(8, UINT32_MAX),
        }
      ), Equals<vector<TSRange>>(
        {
          range(5, 8)
        }
      ));

      AssertThat(get_changed_ranges(
        {
          range(0, 3),
          range(7, 10),
          range(13, 30),
        },
        {
          range(0, 4),
          range(8, 11),
          range(14, 30),
        }
      ), Equals<vector<TSRange>>(
        {
          range(3, 4),
          range(7, 8),
          range(10, 11),
          range(13, 14),
        }
      ));

      AssertThat(get_changed_ranges(
        {
          range(0, UINT32_MAX),
        },
        {
          range(0, 4),
          range(5, 64),
        }
      ), Equals<vector<TSRange>>(
        {
          range(4, 5),
          range(64, UINT32_MAX),
        }
      ));
    });
  });
});

END_TEST
