#ifndef RUNTIME_LEXER_H_
#define RUNTIME_LEXER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"
#include "tree_sitter/runtime.h"
#include "runtime/length.h"
#include "runtime/tree.h"

typedef struct {
  TSLexer data;
  Length current_position;
  Length token_start_position;
  Length token_end_position;

  const char *chunk;
  uint32_t chunk_start;
  uint32_t chunk_size;
  uint32_t lookahead_size;

  TSInput input;
  TSLogger logger;
  char debug_buffer[TREE_SITTER_SERIALIZATION_BUFFER_SIZE];
} Lexer;

void ts_lexer_init(Lexer *);
void ts_lexer_set_input(Lexer *, TSInput);
void ts_lexer_reset(Lexer *, Length);
void ts_lexer_start(Lexer *);
void ts_lexer_advance_to_end(Lexer *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_LEXER_H_
