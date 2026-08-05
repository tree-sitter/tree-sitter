#include "tree_sitter/parser.h"

enum TokenType {
  SURROGATE,
  SUPPLEMENTARY,
};

void *tree_sitter_utf16_surrogate_oob_external_scanner_create(void) { return NULL; }
void tree_sitter_utf16_surrogate_oob_external_scanner_destroy(void *p) {}
unsigned tree_sitter_utf16_surrogate_oob_external_scanner_serialize(void *p, char *b) { return 0; }
void tree_sitter_utf16_surrogate_oob_external_scanner_deserialize(void *p, const char *b, unsigned n) {}

bool tree_sitter_utf16_surrogate_oob_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  int32_t c = lexer->lookahead;

  // Raw surrogate code point (0xD800-0xDFFF): the decoder returned an unpaired
  // surrogate, which is what happens when a lead surrogate is at the end of a chunk.
  //
  // The correct token for `test_utf16_le_decode_does_not_read_oob`
  // The incorrect token for this grammar's corpus test.
  if (c >= 0xD800 && c <= 0xDFFF && valid_symbols[SURROGATE]) {
    lexer->advance(lexer, false);
    lexer->mark_end(lexer);
    lexer->result_symbol = SURROGATE;
    return true;
  }

  // Supplementary-plane character (>0xFFFF): the decoder formed a character from
  // a surrogate pair. For `test_utf16_le_decode_does_not_read_oob`, this should
  // only be possible via an OOB read when the lead surrogate is at the end of a
  // chunk.
  //
  // The incorrect token for `test_utf16_le_decode_does_not_read_oob`
  // The correct token for this grammar's corpus test.
  if (c > 0xFFFF && valid_symbols[SUPPLEMENTARY]) {
    lexer->advance(lexer, false);
    lexer->mark_end(lexer);
    lexer->result_symbol = SUPPLEMENTARY;
    return true;
  }

  return false;
}
