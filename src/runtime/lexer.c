#include <stdio.h>
#include "runtime/lexer.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/debugger.h"
#include "utf8proc.h"

#define DEBUG(...)                                                    \
  if (lexer->debugger.debug_fn) {                                     \
    snprintf(lexer->debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__); \
    lexer->debugger.debug_fn(lexer->debugger.data, TSDebugTypeLex,    \
                             lexer->debug_buffer);                    \
  }

#define DEBUG_LOOKAHEAD()                               \
  DEBUG((0 < lexer->lookahead &&lexer->lookahead < 256) \
            ? "lookahead char:'%c'"                     \
            : "lookahead char:%d",                      \
        lexer->lookahead);

static const char *empty_chunk = "";

static void read_next_chunk(TSLexer *lexer) {
  TSInput input = lexer->input;
  if (lexer->current_position.bytes != lexer->chunk_start + lexer->chunk_size)
    input.seek_fn(input.data, lexer->current_position);

  lexer->chunk_start = lexer->current_position.bytes;
  lexer->chunk = input.read_fn(input.data, &lexer->chunk_size);
  if (!lexer->chunk_size)
    lexer->chunk = empty_chunk;
}

static void read_lookahead(TSLexer *lexer) {
  size_t position_in_chunk = lexer->current_position.bytes - lexer->chunk_start;
  lexer->lookahead_size = utf8proc_iterate(
      (const uint8_t *)lexer->chunk + position_in_chunk,
      lexer->chunk_size - position_in_chunk + 1, &lexer->lookahead);
  DEBUG_LOOKAHEAD();
}

static void start(TSLexer *lexer, TSStateId lex_state) {
  DEBUG("start_lex state:%d", lex_state);
}

static void start_token(TSLexer *lexer) {
  DEBUG("start_token chars:%lu", lexer->current_position.chars);
  lexer->token_start_position = lexer->current_position;
}

static bool advance(TSLexer *lexer, TSStateId state) {
  DEBUG("advance state:%d", state);

  if (lexer->chunk == empty_chunk)
    return false;

  if (lexer->lookahead_size) {
    lexer->current_position.bytes += lexer->lookahead_size;
    lexer->current_position.chars += 1;
  }

  if (lexer->current_position.bytes >= lexer->chunk_start + lexer->chunk_size)
    read_next_chunk(lexer);

  read_lookahead(lexer);
  return true;
}

static TSTree *accept(TSLexer *lexer, TSSymbol symbol, int is_hidden,
                      const char *symbol_name) {
  TSLength size =
      ts_length_sub(lexer->current_position, lexer->token_start_position);
  TSLength padding =
      ts_length_sub(lexer->token_start_position, lexer->token_end_position);
  lexer->token_end_position = lexer->current_position;

  if (symbol == ts_builtin_sym_error) {
    DEBUG_LOOKAHEAD();
    DEBUG("error_char");
    return ts_tree_make_error(size, padding, lexer->lookahead);
  } else {
    DEBUG("accept_token sym:%s", symbol_name);
    return ts_tree_make_leaf(symbol, size, padding, is_hidden);
  }
}

/*
 *  The lexer's methods are stored as struct fields so that generated parsers
 *  can call them without needing to be linked against this library.
 */

TSLexer ts_lexer_make() {
  TSLexer result = (TSLexer) { .start_fn = start,
                               .start_token_fn = start_token,
                               .advance_fn = advance,
                               .accept_fn = accept,
                               .chunk = NULL,
                               .chunk_start = 0,
                               .chunk_size = 0,
                               .current_position = ts_length_zero(),
                               .token_start_position = ts_length_zero(),
                               .token_end_position = ts_length_zero(),
                               .lookahead = 0,
                               .lookahead_size = 0,
                               .debugger = ts_debugger_null() };
  return result;
}

void ts_lexer_reset(TSLexer *lexer, TSLength position) {
  lexer->token_end_position = position;
  lexer->current_position = position;
  read_next_chunk(lexer);
  read_lookahead(lexer);
}
