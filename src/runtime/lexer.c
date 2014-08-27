#include "tree_sitter/parser.h"
#include "runtime/tree.h"

static int advance(TSLexer *lexer) {
  static const char empty_chunk[2] = { '\0', '\0' };
  if (lexer->position_in_chunk + 1 < lexer->chunk_size) {
    lexer->position_in_chunk++;
  } else {
    if (lexer->chunk == empty_chunk)
      return 0;

    lexer->chunk_start += lexer->chunk_size;
    lexer->chunk = lexer->input.read_fn(lexer->input.data, &lexer->chunk_size);
    lexer->position_in_chunk = 0;
    if (lexer->chunk_size == 0) {
      lexer->chunk = empty_chunk;
    }
  }
  return 1;
}

static TSTree *accept(TSLexer *lexer, TSSymbol symbol, int is_hidden) {
  size_t current_position = ts_lexer_position(lexer);
  size_t size = current_position - lexer->token_start_position;
  size_t offset = lexer->token_start_position - lexer->token_end_position;
  lexer->token_end_position = current_position;
  return ts_tree_make_leaf(symbol, size, offset, is_hidden);
}

TSLexer ts_lexer_make() {
  return (TSLexer) { .chunk = NULL,
                     .debug = 0,
                     .chunk_start = 0,
                     .chunk_size = 0,
                     .position_in_chunk = 0,
                     .token_start_position = 0,
                     .token_end_position = 0,
                     .advance_fn = advance,
                     .accept_fn = accept, };
}
