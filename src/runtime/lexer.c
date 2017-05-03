#include <stdio.h>
#include "runtime/lexer.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/utf16.h"
#include "utf8proc.h"

#define LOG(...)                                                              \
  if (self->logger.log) {                                                     \
    snprintf(self->debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__);          \
    self->logger.log(self->logger.payload, TSLogTypeLex, self->debug_buffer); \
  }

#define LOG_CHARACTER(message, character) \
  LOG(character < 255 ? message " character:'%c'" : message " character:%d", character)

static const char empty_chunk[2] = { 0, 0 };

static Length unknown_length = {UINT32_MAX, 0, {0, 0}};

static void ts_lexer__get_chunk(Lexer *self) {
  TSInput input = self->input;
  if (!self->chunk ||
      self->current_position.bytes != self->chunk_start + self->chunk_size)
    input.seek(input.payload, self->current_position.chars,
               self->current_position.bytes);

  self->chunk_start = self->current_position.bytes;
  self->chunk = input.read(input.payload, &self->chunk_size);
  if (!self->chunk_size)
    self->chunk = empty_chunk;
}

static void ts_lexer__get_lookahead(Lexer *self) {
  uint32_t position_in_chunk = self->current_position.bytes - self->chunk_start;
  const uint8_t *chunk = (const uint8_t *)self->chunk + position_in_chunk;
  uint32_t size = self->chunk_size - position_in_chunk + 1;

  if (self->input.encoding == TSInputEncodingUTF8) {
    int64_t lookahead_size = utf8proc_iterate(chunk, size, &self->data.lookahead);
    if (lookahead_size < 0) {
      self->lookahead_size = 1;
    } else {
      self->lookahead_size = lookahead_size;
    }
  }
  else {
    self->lookahead_size = utf16_iterate(chunk, size, &self->data.lookahead);
  }
}

static void ts_lexer__advance(void *payload, bool skip) {
  Lexer *self = (Lexer *)payload;
  if (self->chunk == empty_chunk)
    return;

  if (self->lookahead_size) {
    self->current_position.bytes += self->lookahead_size;
    self->current_position.chars++;
    if (self->data.lookahead == '\n') {
      self->current_position.extent.row++;
      self->current_position.extent.column = 0;
    } else {
      self->current_position.extent.column++;
    }
  }

  if (skip) {
    LOG_CHARACTER("skip", self->data.lookahead);
    self->token_start_position = self->current_position;
  } else {
    LOG_CHARACTER("consume", self->data.lookahead);
  }

  if (self->current_position.bytes >= self->chunk_start + self->chunk_size)
    ts_lexer__get_chunk(self);

  ts_lexer__get_lookahead(self);
}

static void ts_lexer__mark_end(void *payload) {
  Lexer *self = (Lexer *)payload;
  self->token_end_position = self->current_position;
}

/*
 *  The lexer's advance method is stored as a struct field so that generated
 *  parsers can call it without needing to be linked against this library.
 */

void ts_lexer_init(Lexer *self) {
  *self = (Lexer){
    .data = {
      .advance = ts_lexer__advance,
      .mark_end = ts_lexer__mark_end,
      .lookahead = 0,
      .result_symbol = 0,
    },
    .chunk = NULL,
    .chunk_start = 0,
    .logger = {
      .payload = NULL,
      .log = NULL
    },
    .last_external_token_state = NULL,
  };
  ts_lexer_reset(self, length_zero());
}

static inline void ts_lexer__reset(Lexer *self, Length position) {
  self->token_start_position = position;
  self->token_end_position = unknown_length;
  self->current_position = position;

  if (self->chunk && (position.bytes < self->chunk_start ||
                      position.bytes >= self->chunk_start + self->chunk_size)) {
    self->chunk = 0;
    self->chunk_start = 0;
    self->chunk_size = 0;
  }

  self->lookahead_size = 0;
  self->data.lookahead = 0;
}

void ts_lexer_set_input(Lexer *self, TSInput input) {
  self->input = input;
  ts_lexer__reset(self, length_zero());
  self->last_external_token_state = NULL;
}

void ts_lexer_reset(Lexer *self, Length position) {
  if (position.bytes != self->current_position.bytes) {
    ts_lexer__reset(self, position);
  }
}

void ts_lexer_start(Lexer *self) {
  self->token_start_position = self->current_position;
  self->token_end_position = unknown_length;
  self->data.result_symbol = 0;

  if (!self->chunk)
    ts_lexer__get_chunk(self);
  if (!self->lookahead_size)
    ts_lexer__get_lookahead(self);
}

void ts_lexer_advance_to_end(Lexer *self) {
  while (self->data.lookahead != 0) ts_lexer__advance(self, false);
}
