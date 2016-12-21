#ifndef RUNTIME_LEXER_H_
#define RUNTIME_LEXER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"
#include "tree_sitter/runtime.h"
#include "runtime/length.h"

#define TS_DEBUG_BUFFER_SIZE 512

typedef struct {
  TSLexer data;
  Length current_position;
  Length token_start_position;

  const char *chunk;
  uint32_t chunk_start;
  uint32_t chunk_size;

  uint32_t lookahead_size;

  TSInput input;
  TSLogger logger;
  char debug_buffer[TS_DEBUG_BUFFER_SIZE];
  bool needs_to_restore_external_scanner;
  uint32_t last_external_token_end_byte;
} Lexer;

void ts_lexer_init(Lexer *);
void ts_lexer_set_input(Lexer *, TSInput);
void ts_lexer_reset(Lexer *, Length);
void ts_lexer_start(Lexer *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_LEXER_H_
