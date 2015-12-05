#include <stdio.h>
#include "runtime/lexer.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/debugger.h"
#include "utf8proc.h"

#define LOG(...)                                                     \
  if (self->debugger.debug_fn) {                                     \
    snprintf(self->debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__); \
    self->debugger.debug_fn(self->debugger.payload, TSDebugTypeLex,  \
                            self->debug_buffer);                     \
  }

#define LOG_LOOKAHEAD()                                                      \
  LOG((0 < self->lookahead && self->lookahead < 256) ? "lookahead char:'%c'" \
                                                     : "lookahead char:%d",  \
      self->lookahead);

static const char *empty_chunk = "";

static void ts_lexer__get_chunk(TSLexer *self) {
  TSInput input = self->input;
  if (!self->chunk ||
      self->current_position.bytes != self->chunk_start + self->chunk_size)
    input.seek_fn(input.payload, self->current_position.chars, self->current_position.bytes);

  self->chunk_start = self->current_position.bytes;
  self->chunk = input.read_fn(input.payload, &self->chunk_size);
  if (!self->chunk_size)
    self->chunk = empty_chunk;
}

static void ts_lexer__get_lookahead(TSLexer *self) {
  size_t position_in_chunk = self->current_position.bytes - self->chunk_start;
  self->lookahead_size = utf8proc_iterate(
    (const uint8_t *)self->chunk + position_in_chunk,
    self->chunk_size - position_in_chunk + 1, &self->lookahead);
  LOG_LOOKAHEAD();
}

static void ts_lexer__start(TSLexer *self, TSStateId lex_state) {
  LOG("start_lex state:%d, pos:%lu", lex_state, self->current_position.chars);
  LOG_LOOKAHEAD();

  if (!self->chunk)
    ts_lexer__get_chunk(self);
  if (!self->lookahead_size)
    ts_lexer__get_lookahead(self);
}

static void ts_lexer__start_token(TSLexer *self) {
  LOG("start_token chars:%lu, rows:%lu, columns:%lu", self->current_position.chars, self->current_position.rows, self->current_position.columns);
  self->token_start_position = self->current_position;
}

static bool ts_lexer__advance(TSLexer *self, TSStateId state) {
  LOG("advance state:%d", state);

  if (self->chunk == empty_chunk)
    return false;

  if (self->lookahead_size) {
    self->current_position.bytes += self->lookahead_size;
    self->current_position.chars++;

    if (self->lookahead == '\n') {
      self->current_position.rows++;
      self->current_position.columns = 0;
    } else {
      self->current_position.columns++;
    }
  }

  if (self->current_position.bytes >= self->chunk_start + self->chunk_size)
    ts_lexer__get_chunk(self);

  ts_lexer__get_lookahead(self);
  return true;
}

static TSTree *ts_lexer__accept(TSLexer *self, TSSymbol symbol,
                                TSSymbolMetadata metadata,
                                const char *symbol_name) {
  TSLength size = ts_length_sub(self->current_position, self->token_start_position);
  TSLength padding = ts_length_sub(self->token_start_position, self->token_end_position);
  self->token_end_position = self->current_position;

  if (symbol == ts_builtin_sym_error) {
    LOG("error_char");
    return ts_tree_make_error(size, padding, self->lookahead);
  } else {
    LOG("accept_token sym:%s", symbol_name);
    return ts_tree_make_leaf(symbol, padding, size, metadata);
  }
}

/*
 *  The lexer's methods are stored as struct fields so that generated parsers
 *  can call them without needing to be linked against this library.
 */

TSLexer ts_lexer_make() {
  TSLexer result = (TSLexer){
    .start_fn = ts_lexer__start,
    .start_token_fn = ts_lexer__start_token,
    .advance_fn = ts_lexer__advance,
    .accept_fn = ts_lexer__accept,
    .chunk = NULL,
    .chunk_start = 0,
    .debugger = ts_debugger_null(),
  };
  ts_lexer_reset(&result, ts_length_zero());
  return result;
}

static inline void ts_lexer__reset(TSLexer *self, TSLength position) {
  self->token_start_position = position;
  self->token_end_position = position;
  self->current_position = position;

  self->chunk = 0;
  self->chunk_start = 0;
  self->chunk_size = 0;
  self->lookahead_size = 0;
  self->lookahead = 0;
}

void ts_lexer_set_input(TSLexer *self, TSInput input) {
  self->input = input;
  ts_lexer__reset(self, ts_length_zero());
}

void ts_lexer_reset(TSLexer *self, TSLength position) {
  if (!ts_length_eq(position, self->current_position))
    ts_lexer__reset(self, position);
    return;
}
