#include <string.h>
#include "tree_sitter/runtime.h"

void test_log(void *payload, TSLogType type, const char *string) { }

TSLogger logger = {
  .log = test_log,
};

extern "C" const TSLanguage *TS_LANG();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *str = reinterpret_cast<const char *>(data);

  TSDocument *document = ts_document_new();
  ts_document_set_language(document, TS_LANG());
  ts_document_set_input_string_with_length(document, str, size);

  TSParseOptions options = {};
  options.halt_on_error = TS_HALT_ON_ERROR;
  ts_document_parse_with_options(document, options);

  TSNode root_node = ts_document_root_node(document);
  ts_document_free(document);

  return 0;
}
