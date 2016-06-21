#ifndef RUNTIME_LEXER_H_
#define RUNTIME_LEXER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"

typedef struct {
  TSSymbol symbol;
  TSLength padding;
  TSLength size;
  int32_t first_unexpected_character;
} TSLexerResult;

void ts_lexer_init(TSLexer *);
void ts_lexer_set_input(TSLexer *, TSInput);
void ts_lexer_reset(TSLexer *, TSLength);
void ts_lexer_start(TSLexer *, TSStateId);
void ts_lexer_finish(TSLexer *, TSLexerResult *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_LEXER_H_
