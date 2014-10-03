#include "runtime/lexer.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "utf8proc.h"

static const char *empty_chunk = "";

static bool advance(TSLexer *lexer) {

  /*
   *  Return false if the Lexer has already reached the end of the input.
   */
  if (lexer->chunk == empty_chunk)
    return false;

  /*
   *  Increment the Lexer's position.
   */
  if (lexer->lookahead_size) {
    lexer->current_position.bytes += lexer->lookahead_size;
    lexer->current_position.chars += 1;
  }

  /*
   *  Request a new chunk of text from the Input if the Lexer has reached
   *  the end of the current chunk.
   */
  if (lexer->current_position.bytes >= lexer->chunk_start + lexer->chunk_size) {
    lexer->chunk_start += lexer->chunk_size;
    lexer->chunk = lexer->input.read_fn(lexer->input.data, &lexer->chunk_size);
    if (!lexer->chunk_size)
      lexer->chunk = empty_chunk;
  }

  /*
   *  Read the next unicode character from the current chunk of text.
   */
  size_t position_in_chunk = lexer->current_position.bytes - lexer->chunk_start;
  lexer->lookahead_size = utf8proc_iterate(
      (const uint8_t *)lexer->chunk + position_in_chunk,
      lexer->chunk_size - position_in_chunk + 1, &lexer->lookahead);

  return true;
}

static TSTree *accept(TSLexer *lexer, TSSymbol symbol, int is_hidden) {
  TSLength size =
      ts_length_sub(lexer->current_position, lexer->token_start_position);
  TSLength padding =
      ts_length_sub(lexer->token_start_position, lexer->token_end_position);
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
  TSLexer result =
      (TSLexer) { .debug = 0, .advance_fn = advance, .accept_fn = accept, };
  ts_lexer_reset(&result);
  return result;
}

void ts_lexer_reset(TSLexer *lexer) {
  lexer->chunk = NULL;
  lexer->chunk_start = 0;
  lexer->chunk_size = 0;
  lexer->current_position = ts_length_zero();
  lexer->token_start_position = ts_length_zero();
  lexer->token_end_position = ts_length_zero();
  lexer->lookahead = 0;
  lexer->lookahead_size = 0;
}
