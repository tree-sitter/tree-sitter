#include <cassert>
#include <fstream>
#include "tree_sitter/api.h"

extern "C" const TSLanguage *TS_LANG();

static TSQuery *lang_query;

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
  if(TS_LANG_QUERY_FILENAME[0]) {
    // The query filename is relative to the fuzzing binary. Convert it
    // to an absolute path first
    auto binary_filename = std::string((*argv)[0]);
    auto binary_directory = binary_filename.substr(0, binary_filename.find_last_of("\\/"));
    auto lang_query_filename = binary_directory + "/" + TS_LANG_QUERY_FILENAME;

    auto f = std::ifstream(lang_query_filename);
    assert(f.good());
    std::string lang_query_source((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

    uint32_t error_offset = 0;
    TSQueryError error_type = TSQueryErrorNone;

    lang_query = ts_query_new(
      TS_LANG(),
      lang_query_source.c_str(),
      lang_query_source.size(),
      &error_offset,
      &error_type
    );

    assert(lang_query);
  }

  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *str = reinterpret_cast<const char *>(data);

  TSParser *parser = ts_parser_new();

  // This can fail if the language version doesn't match the runtime version
  bool language_ok = ts_parser_set_language(parser, TS_LANG());
  assert(language_ok);

  TSTree *tree = ts_parser_parse_string(parser, NULL, str, size);
  TSNode root_node = ts_tree_root_node(tree);

  if (lang_query) {
    {
      TSQueryCursor *cursor = ts_query_cursor_new();

      ts_query_cursor_exec(cursor, lang_query, root_node);
      TSQueryMatch match;
      while (ts_query_cursor_next_match(cursor, &match)) {
      }

      ts_query_cursor_delete(cursor);
    }

    {
      TSQueryCursor *cursor = ts_query_cursor_new();

      ts_query_cursor_exec(cursor, lang_query, root_node);
      TSQueryMatch match;
      uint32_t capture_index;
      while (ts_query_cursor_next_capture(cursor, &match, &capture_index)) {
      }

      ts_query_cursor_delete(cursor);
    }
  }

  ts_tree_delete(tree);
  ts_parser_delete(parser);

  return 0;
}
