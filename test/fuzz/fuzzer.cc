#include <string.h>
#include "tree_sitter/runtime.h"

void test_log(void *payload, TSLogType type, const char *string) { }

TSLogger logger = {
  .log = test_log,
};

extern "C" const TSLanguage *TS_LANG();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *str = reinterpret_cast<const char *>(data);

  TSParser *parser = ts_parser_new();
  ts_parser_set_language(parser, TS_LANG());
  ts_parser_halt_on_error(parser, TS_HALT_ON_ERROR);

  TSTree *tree = ts_parser_parse_string(parser, NULL, str, size);
  TSNode root_node = ts_tree_root_node(tree);

  ts_tree_delete(tree);
  ts_parser_delete(parser);

  return 0;
}
