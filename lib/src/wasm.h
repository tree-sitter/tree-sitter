#ifndef TREE_SITTER_WASM_H_
#define TREE_SITTER_WASM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "./array.h"
#include "./wasm/wasm.h"
#include "./lexer.h"

typedef struct {
  uint32_t id;
  wasm_instance_t *instance;
  uint32_t main_lex_fn_index;
  uint32_t keyword_lex_fn_index;
  uint32_t external_scan_index;
} LanguageInstance;

struct TSWasmStore {
  wasm_store_t *store;
  wasm_table_t *function_table;
  wasm_memory_t *memory;
  TSLexer *current_lexer;
  LanguageInstance *current_instance;
  Array(LanguageInstance) language_instances;
};

struct TSWasmLanguage {
  uint32_t id;
  volatile uint32_t ref_count;
  wasm_shared_module_t *module;
  TSLanguage *language;
  const char *name;
  char *symbol_name_buffer;
  char *field_name_buffer;
};

void ts_wasm_language_retain(const TSWasmLanguage *);
bool ts_wasm_store_start(TSWasmStore *self, TSLexer *lexer, const TSWasmLanguage *language);
void ts_wasm_store_stop(TSWasmStore *self);

static inline bool ts_wasm_store_run_main_lex_function(TSWasmStore *self, TSStateId state) {
  uint32_t function_index = self->current_instance->main_lex_fn_index;
  wasm_ref_t *lex_ref = wasm_table_get(self->function_table, function_index);
  wasm_func_t *lex_func = wasm_ref_as_func(lex_ref);
  wasm_val_t args_list[2] = {
    WASM_I32_VAL(state),
    WASM_I32_VAL(state),
  };
  wasm_val_t results_list[1] = {
    WASM_I32_VAL(0),
  };
  wasm_val_vec_t args = WASM_ARRAY_VEC(args_list);
  wasm_val_vec_t results = WASM_ARRAY_VEC(results_list);
  wasm_func_call(lex_func, &args, &results);
  assert(results_list[0].kind == WASM_I32);
  return results_list[0].of.i32;
}

static inline bool ts_wasm_store_run_keyword_lex_function(TSWasmStore *self, TSStateId state) {
  uint32_t function_index = self->current_instance->keyword_lex_fn_index;
  wasm_ref_t *lex_ref = wasm_table_get(self->function_table, function_index);
  wasm_func_t *lex_func = wasm_ref_as_func(lex_ref);
  wasm_val_t args_list[2] = {
    WASM_I32_VAL(state),
    WASM_I32_VAL(state),
  };
  wasm_val_t results_list[1] = {
    WASM_I32_VAL(0),
  };
  wasm_val_vec_t args = WASM_ARRAY_VEC(args_list);
  wasm_val_vec_t results = WASM_ARRAY_VEC(results_list);
  wasm_func_call(lex_func, &args, &results);
  assert(results_list[0].kind == WASM_I32);
  return results_list[0].of.i32;
}

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_WASM_H_
