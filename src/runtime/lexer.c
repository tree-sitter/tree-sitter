#include <stdio.h>
#include "runtime/lexer.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/utf16.h"
#include "utf8proc.h"

#define LOG(...)                                                     \
  if (self->logger.log) {                                     \
    snprintf(self->debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__); \
    self->logger.log(self->logger.payload, TSLogTypeLex,  \
                            self->debug_buffer);                     \
  }

#define LOG_LOOKAHEAD()                                                      \
  LOG((0 < self->lookahead && self->lookahead < 256) ? "lookahead char:'%c'" \
                                                     : "lookahead char:%d",  \
      self->lookahead);

static const char empty_chunk[2] = { 0, 0 };

static void ts_lexer__get_chunk(TSLexer *self) {
  TSInput input = self->input;
  if (!self->chunk ||
      self->current_position.bytes != self->chunk_start + self->chunk_size)
    input.seek_fn(input.payload, self->current_position.chars,
                  self->current_position.bytes);

  self->chunk_start = self->current_position.bytes;
  self->chunk = input.read_fn(input.payload, &self->chunk_size);
  if (!self->chunk_size)
    self->chunk = empty_chunk;
}

static void ts_lexer__get_lookahead(TSLexer *self) {
  size_t position_in_chunk = self->current_position.bytes - self->chunk_start;
  const uint8_t *chunk = (const uint8_t *)self->chunk + position_in_chunk;
  size_t size = self->chunk_size - position_in_chunk + 1;

  if (self->input.encoding == TSInputEncodingUTF8)
    self->lookahead_size = utf8proc_iterate(chunk, size, &self->lookahead);
  else
    self->lookahead_size = utf16_iterate(chunk, size, &self->lookahead);

  LOG_LOOKAHEAD();
}

static void ts_lexer__advance(TSLexer *self, TSStateId state, bool skip) {

  if (self->chunk == empty_chunk)
    return;

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

  if (skip) {
    LOG("skip_separator state:%d", state);
    self->token_start_position = self->current_position;
  } else {
    LOG("advance state:%d", state);
  }

  if (self->current_position.bytes >= self->chunk_start + self->chunk_size)
    ts_lexer__get_chunk(self);

  ts_lexer__get_lookahead(self);
}

/*
 *  The lexer's advance method is stored as a struct field so that generated
 *  parsers can call it without needing to be linked against this library.
 */

void ts_lexer_init(TSLexer *self) {
  *self = (TSLexer){
    .advance = ts_lexer__advance,
    .chunk = NULL,
    .chunk_start = 0,
    .logger = {},
  };
  ts_lexer_reset(self, ts_length_zero());
}

static inline void ts_lexer__reset(TSLexer *self, TSLength position) {
  self->token_start_position = position;
  self->current_position = position;

  if (self->chunk && (position.bytes < self->chunk_start || position.bytes >= self->chunk_start + self->chunk_size)) {
    self->chunk = 0;
    self->chunk_start = 0;
    self->chunk_size = 0;
  }

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

void ts_lexer_start(TSLexer *self, TSStateId lex_state) {
  LOG("start_lex state:%d, pos:%lu", lex_state, self->current_position.chars);

  self->token_start_position = self->current_position;
  self->result_symbol = 0;

  if (!self->chunk)
    ts_lexer__get_chunk(self);
  if (!self->lookahead_size)
    ts_lexer__get_lookahead(self);
}
