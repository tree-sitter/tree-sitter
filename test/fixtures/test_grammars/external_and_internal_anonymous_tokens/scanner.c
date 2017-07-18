#include "../external_and_internal_tokens/scanner.c"

void *tree_sitter_external_and_internal_anonymous_tokens_external_scanner_create() {
  return NULL;
}

void tree_sitter_external_and_internal_anonymous_tokens_external_scanner_destroy(
  void *payload
) {}

void tree_sitter_external_and_internal_anonymous_tokens_external_scanner_reset(
  void *payload
) {}

unsigned tree_sitter_external_and_internal_anonymous_tokens_external_scanner_serialize(
  void *payload,
  char *buffer
) { return 0; }

void tree_sitter_external_and_internal_anonymous_tokens_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {}

bool tree_sitter_external_and_internal_anonymous_tokens_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *whitelist
) {
  return tree_sitter_external_and_internal_tokens_external_scanner_scan(
    payload,
    lexer,
    whitelist
  );
}
