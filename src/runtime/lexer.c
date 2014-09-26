#include "runtime/lexer.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "utf8proc.h"

static int advance(TSLexer *lexer) {
  static const char *empty_chunk = "";

  lexer->lookahead = 0;

  if (lexer->chunk == empty_chunk) {
    lexer->lookahead_size = 0;
    return 0;
  }

  if (lexer->chunk_start + lexer->chunk_size <= lexer->current_position.bytes + 1) {
    if (lexer->lookahead_size) {
      lexer->current_position.bytes += lexer->lookahead_size;
      lexer->current_position.chars += 1;
    }
    lexer->lookahead_size = 0;
    lexer->chunk_start += lexer->chunk_size;
    lexer->chunk = lexer->input.read_fn(lexer->input.data, &lexer->chunk_size);
  }

  if (lexer->chunk_size == 0) {
    lexer->lookahead_size = 0;
    lexer->chunk = empty_chunk;
  } else {
    if (lexer->lookahead_size) {
      lexer->current_position.bytes += lexer->lookahead_size;
      lexer->current_position.chars += 1;
    }

    lexer->lookahead_size = utf8proc_iterate(
        (const uint8_t *)lexer->chunk + (lexer->current_position.bytes - lexer->chunk_start),
        lexer->chunk_start + lexer->chunk_size - lexer->current_position.bytes + 1,
        &lexer->lookahead);
  }

  return 1;
}

static TSTree *accept(TSLexer *lexer, TSSymbol symbol, int is_hidden) {
  TSLength size = ts_length_sub(lexer->current_position, lexer->token_start_position);
  TSLength padding = ts_length_sub(lexer->token_start_position, lexer->token_end_position);
  lexer->token_end_position = lexer->current_position;
  return (symbol == ts_builtin_sym_error)
             ? ts_tree_make_error(size, padding, ts_lexer_lookahead_char(lexer))
             : ts_tree_make_leaf(symbol, size, padding, is_hidden);
}

/*
 *  The `advance` and `accept` methods are stored as fields on the Lexer so
 *  that generated parsers can call them without needing to be linked against
 *  this library.
 */
TSLexer ts_lexer_make() {
  TSLexer result = (TSLexer) { .debug = 0,
                               .advance_fn = advance,
                               .accept_fn = accept, };
  ts_lexer_reset(&result);
  return result;
}

void ts_lexer_reset(TSLexer *lexer) {
  lexer->chunk = NULL;
  lexer->chunk_start = 0;
  lexer->chunk_size = 0;
  lexer->current_position = ts_length_zero(),
  lexer->token_start_position = ts_length_zero(),
  lexer->token_end_position = ts_length_zero(),
  lexer->lookahead = 0;
  lexer->lookahead_size = 0;
}
