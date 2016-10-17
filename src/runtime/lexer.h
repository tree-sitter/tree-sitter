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
  TSLength current_position;
  TSLength token_start_position;

  const char *chunk;
  size_t chunk_start;
  size_t chunk_size;

  size_t lookahead_size;

  TSInput input;
  TSLogger logger;
  char debug_buffer[TS_DEBUG_BUFFER_SIZE];
} Lexer;

void ts_lexer_init(Lexer *);
void ts_lexer_set_input(Lexer *, TSInput);
void ts_lexer_reset(Lexer *, TSLength);
void ts_lexer_start(Lexer *, TSStateId);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_LEXER_H_
