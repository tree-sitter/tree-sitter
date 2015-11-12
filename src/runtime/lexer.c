#include <stdio.h>
#include "runtime/lexer.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/length.h"
#include "runtime/debugger.h"
#include "utf8proc.h"

#define DEBUG(...)                                                   \
  if (self->debugger.debug_fn) {                                     \
    snprintf(self->debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__); \
    self->debugger.debug_fn(self->debugger.payload, TSDebugTypeLex,  \
                            self->debug_buffer);                     \
  }

#define DEBUG_LOOKAHEAD()                                                      \
  DEBUG((0 < self->lookahead && self->lookahead < 256) ? "lookahead char:'%c'" \
                                                       : "lookahead char:%d",  \
        self->lookahead);

static const char *empty_chunk = "";

static void ts_lexer__get_chunk(TSLexer *self) {
  TSInput input = self->input;
  if (!self->chunk ||
      self->current_position.bytes != self->chunk_start + self->chunk_size)
    input.seek_fn(input.payload, self->current_position);

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
  DEBUG_LOOKAHEAD();
}

static void ts_lexer__start(TSLexer *self, TSStateId lex_state) {
  DEBUG("start_lex state:%d, pos:%lu", lex_state, self->current_position.chars);
  DEBUG_LOOKAHEAD();

  if (!self->chunk)
    ts_lexer__get_chunk(self);
  if (!self->lookahead_size)
    ts_lexer__get_lookahead(self);
}

static void ts_lexer__start_token(TSLexer *self) {
  DEBUG("start_token chars:%lu", self->current_position.chars);
  self->token_start_position = self->current_position;

  DEBUG("start_token line:%lu", self->current_source_info.line);
  DEBUG("start_token column:%lu", self->current_source_info.column);
  self->token_start_source_info = self->current_source_info;
}

static bool ts_lexer__advance(TSLexer *self, TSStateId state) {
  DEBUG("advance state:%d", state);

  if (self->chunk == empty_chunk)
    return false;

  if (self->lookahead_size) {
    self->current_position.bytes += self->lookahead_size;
    self->current_position.chars += 1;

		if (self->lookahead == '\n') {
			self->current_source_info.line += 1;
			self->current_source_info.column = 0;
		} else {
			self->current_source_info.column += 1;
		}
  }

  if (self->current_position.bytes >= self->chunk_start + self->chunk_size)
    ts_lexer__get_chunk(self);

  ts_lexer__get_lookahead(self);
  return true;
}

static TSTree *ts_lexer__accept(TSLexer *self, TSSymbol symbol,
                                TSNodeType node_type, const char *symbol_name) {
  TSLength size =
    ts_length_sub(self->current_position, self->token_start_position);
  TSLength padding =
    ts_length_sub(self->token_start_position, self->token_end_position);
  self->token_end_position = self->current_position;

	self->token_end_source_info = self->current_source_info;

  if (symbol == ts_builtin_sym_error) {
    DEBUG("error_char");
    return ts_tree_make_error(size, padding, self->token_start_source_info,
															self->token_end_source_info, self->lookahead);
  } else {
    DEBUG("accept_token sym:%s", symbol_name);
    return ts_tree_make_leaf(symbol, padding, size,
														 self->token_start_source_info,
														 self->token_end_source_info, node_type);
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

void ts_lexer_reset(TSLexer *self, TSLength position) {
  self->token_start_position = position;
  self->token_end_position = position;
  self->current_position = position;
  self->chunk = 0;
  self->chunk_start = 0;
  self->chunk_size = 0;
  self->lookahead_size = 0;
  self->lookahead = 0;
}
