#ifndef RUNTIME_LEXER_H_
#define RUNTIME_LEXER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"

void ts_lexer_init(TSLexer *);
void ts_lexer_set_input(TSLexer *, TSInput);
void ts_lexer_reset(TSLexer *, TSLength);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_LEXER_H_
