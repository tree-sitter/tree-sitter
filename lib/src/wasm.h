#ifndef TREE_SITTER_WASM_H_
#define TREE_SITTER_WASM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/api.h"
#include "tree_sitter/parser.h"

bool ts_wasm_store_start(TSWasmStore *self, TSLexer *lexer, const TSLanguage *language);
void ts_wasm_store_stop(TSWasmStore *self);
bool ts_wasm_store_run_main_lex_function(TSWasmStore *self, TSStateId state);
bool ts_wasm_store_run_keyword_lex_function(TSWasmStore *self, TSStateId state);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_WASM_H_
