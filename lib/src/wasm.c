#include "tree_sitter/api.h"
#include "./wasm/wasm.h"
#include "./alloc.h"
#include "./language.h"
#include "./array.h"
#include "./atomic.h"
#include "./lexer.h"
#include "./wasm.h"

static volatile uint32_t NEXT_LANGUAGE_ID;

typedef Array(char) StringData;

typedef struct {
  uint32_t version;
  uint32_t symbol_count;
  uint32_t alias_count;
  uint32_t token_count;
  uint32_t external_token_count;
  uint32_t state_count;
  uint32_t large_state_count;
  uint32_t production_id_count;
  uint32_t field_count;
  uint16_t max_alias_sequence_length;
  int32_t parse_table;
  int32_t small_parse_table;
  int32_t small_parse_table_map;
  int32_t parse_actions;
  int32_t symbol_names;
  int32_t field_names;
  int32_t field_map_slices;
  int32_t field_map_entries;
  int32_t symbol_metadata;
  int32_t public_symbol_map;
  int32_t alias_map;
  int32_t alias_sequences;
  int32_t lex_modes;
  int32_t lex_fn;
  int32_t keyword_lex_fn;
  TSSymbol keyword_capture_token;
  struct {
    int32_t states;
    int32_t symbol_map;
    int32_t create;
    int32_t destroy;
    int32_t scan;
    int32_t serialize;
    int32_t deserialize;
  } external_scanner;
  int32_t primary_state_ids;
} LanguageInWasmMemory;

typedef struct {
  int32_t lookahead;
  TSSymbol result_symbol;
  int32_t advance;
  int32_t mark_end;
  int32_t get_column;
  int32_t is_at_included_range_start;
  int32_t eof;
  void *native_lexer_address;
} LexerInWasmMemory;

static wasm_trap_t *advance_callback(
  void *env,
  const wasm_val_vec_t *args,
  wasm_val_vec_t *results
) {
  assert(args->size == 2);
  assert(args->data[0].kind == WASM_I32);
  assert(args->data[1].kind == WASM_I32);

  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  int32_t lexer_address = args->data[0].of.i32;
  bool skip = args->data[1].of.i32;

  lexer->advance(lexer, skip);
  char *memory = wasm_memory_data(store->memory);
  memcpy(&memory[lexer_address], &lexer->lookahead, sizeof(lexer->lookahead));
  return NULL;
}

static wasm_trap_t *mark_end_callback(
  void *env,
  const wasm_val_vec_t *args,
  wasm_val_vec_t *results
) {
  assert(args->size == 1);
  assert(args->data[0].kind == WASM_I32);
  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  lexer->mark_end(lexer);
  return NULL;
}

static wasm_trap_t *get_column_callback(
  void *env,
  const wasm_val_vec_t *args,
  wasm_val_vec_t *results
) {
  assert(args->size == 1);
  assert(args->data[0].kind == WASM_I32);
  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  wasm_val_t result = WASM_I32_VAL(lexer->get_column(lexer));
  results->data[0] = result;
  return NULL;
}

static wasm_trap_t *is_at_included_range_start_callback(
  void *env,
  const wasm_val_vec_t *args,
  wasm_val_vec_t *results
) {
  assert(args->size == 1);
  assert(args->data[0].kind == WASM_I32);
  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  wasm_val_t result = WASM_I32_VAL(lexer->is_at_included_range_start(lexer));
  results->data[0] = result;
  return NULL;
}

static wasm_trap_t *eof_callback(
  void *env,
  const wasm_val_vec_t *args,
  wasm_val_vec_t *results
) {
  assert(args->size == 1);
  assert(args->data[0].kind == WASM_I32);
  TSWasmStore *store = env;
  TSLexer *lexer = store->current_lexer;
  wasm_val_t result = WASM_I32_VAL(lexer->eof(lexer));
  results->data[0] = result;
  return NULL;
}

typedef struct {
  wasm_func_callback_with_env_t callback;
  wasm_functype_t *type;
} FunctionDefinition;

#define array_len(a) (sizeof(a) / sizeof(a[0]))

static void *copy(const void *data, size_t size) {
  void *result = ts_malloc(size);
  memcpy(result, data, size);
  return result;
}

static void *copy_strings(
  const char *data,
  int32_t array_address,
  size_t count,
  StringData *string_data
) {
  const char **result = ts_malloc(count * sizeof(char *));
  for (unsigned i = 0; i < count; i++) {
    int32_t address;
    memcpy(&address, &data[array_address + i * sizeof(address)], sizeof(address));
    const char *string = &data[address];
    uint32_t len = strlen(string);
    result[i] = (const char *)(uintptr_t)string_data->size;
    array_extend(string_data, len + 1, string);
  }
  for (unsigned i = 0; i < count; i++) {
    result[i] = string_data->contents + (uintptr_t)result[i];
  }
  return result;
}

static bool name_eq(const wasm_name_t *name, const char *string) {
  return strncmp(string, name->data, name->size) == 0;
}

TSWasmStore *ts_wasm_store_new(TSWasmEngine *engine) {
  TSWasmStore *self = ts_malloc(sizeof(TSWasmStore));
  wasm_store_t *store = wasm_store_new(engine);

  // Memory
  wasm_limits_t memory_limits = {.min = 64, .max = wasm_limits_max_default};
  wasm_memorytype_t *memory_type = wasm_memorytype_new(&memory_limits);
  wasm_memory_t *memory = wasm_memory_new(store, memory_type);
  wasm_memorytype_delete(memory_type);

  // Lexer functions
  FunctionDefinition definitions[] = {
    {advance_callback, wasm_functype_new_2_0(wasm_valtype_new_i32(), wasm_valtype_new_i32())},
    {mark_end_callback, wasm_functype_new_1_0(wasm_valtype_new_i32())},
    {get_column_callback, wasm_functype_new_1_1(wasm_valtype_new_i32(), wasm_valtype_new_i32())},
    {is_at_included_range_start_callback, wasm_functype_new_1_1(wasm_valtype_new_i32(), wasm_valtype_new_i32())},
    {eof_callback, wasm_functype_new_1_1(wasm_valtype_new_i32(), wasm_valtype_new_i32())},
  };
  unsigned definitions_len = array_len(definitions);

  // Function table
  wasm_limits_t table_limits = {.min = definitions_len, .max = wasm_limits_max_default};
  wasm_tabletype_t *table_type = wasm_tabletype_new(wasm_valtype_new(WASM_FUNCREF), &table_limits);
  wasm_table_t *function_table = wasm_table_new(store, table_type, NULL);
  wasm_tabletype_delete(table_type);

  wasm_table_grow(function_table, definitions_len, NULL);
  for (unsigned i = 0; i < definitions_len; i++) {
    FunctionDefinition *definition = &definitions[i];
    wasm_func_t *func = wasm_func_new_with_env(store, definition->type, definition->callback, self, NULL);
    wasm_table_set(function_table, i, (wasm_ref_t *)func);
    wasm_functype_delete(definition->type);
  }

  *self = (TSWasmStore) {
    .store = store,
    .memory = memory,
    .language_instances = array_new(),
    .function_table = function_table,
  };
  return self;
}

void ts_wasm_store_delete(TSWasmStore *self) {
  wasm_memory_delete(self->memory);
  wasm_table_delete(self->function_table);
  wasm_store_delete(self->store);
  array_delete(&self->language_instances);
  ts_free(self);
}

void ts_wasm_language_delete(const TSWasmLanguage *self) {
  assert(self->ref_count > 0);
  if (atomic_dec((volatile uint32_t *)&self->ref_count) == 0) {
    wasm_shared_module_delete(self->module);
    ts_free((void *)self->language->alias_map);
    ts_free((void *)self->language->alias_sequences);
    ts_free((void *)self->language->parse_table);
    ts_free((void *)self->language->parse_actions);
    ts_free((void *)self->language->primary_state_ids);
    ts_free((void *)self->language->public_symbol_map);
    ts_free(self->language);
    ts_free(self->symbol_name_buffer);
    ts_free(self->field_name_buffer);
    ts_free((void *)self);
  }
}

void ts_wasm_language_retain(const TSWasmLanguage *self) {
  atomic_inc((volatile uint32_t *)&self->ref_count);
}

static bool ts_wasm_store__instantiate(
  TSWasmStore *self,
  wasm_module_t *module,
  const char *language_name,
  wasm_instance_t **result,
  int32_t *language_address
) {
  // Build language function name string.
  unsigned prefix_len = strlen("tree_sitter_");
  unsigned name_len = strlen(language_name);
  char language_function_name[prefix_len + name_len + 1];
  memcpy(&language_function_name[0], "tree_sitter_", prefix_len);
  memcpy(&language_function_name[prefix_len], language_name, name_len);
  language_function_name[prefix_len + name_len] = '\0';

  wasm_importtype_vec_t import_types = WASM_EMPTY_VEC;
  wasm_module_imports(module, &import_types);

  wasm_globaltype_t *const_i32_type = wasm_globaltype_new(wasm_valtype_new_i32(), WASM_CONST);
  wasm_val_t table_base_val = WASM_I32_VAL(5);
  wasm_val_t memory_base_val = WASM_I32_VAL(1600);
  wasm_global_t *memory_base_global = wasm_global_new(self->store, const_i32_type, &memory_base_val);
  wasm_global_t *table_base_global = wasm_global_new(self->store, const_i32_type, &table_base_val);
  wasm_globaltype_delete(const_i32_type);

  // Build imports list
  printf("import count: %lu\n", import_types.size);
  wasm_extern_t *imports_list[import_types.size];
  wasm_extern_vec_t imports = WASM_ARRAY_VEC(imports_list);
  for (unsigned i = 0; i < import_types.size; i++) {
    const wasm_importtype_t *import_type = import_types.data[i];
    const wasm_name_t *import_name = wasm_importtype_name(import_type);

    if (name_eq(import_name, "__memory_base")) {
      imports.data[i] = wasm_global_as_extern(memory_base_global);
    } else if (name_eq(import_name, "__table_base")) {
      imports.data[i] = wasm_global_as_extern(table_base_global);
    } else if (name_eq(import_name, "memory")) {
      imports.data[i] = wasm_memory_as_extern(self->memory);
    } else if (name_eq(import_name, "__indirect_function_table")) {
      imports.data[i] = wasm_table_as_extern(self->function_table);
    } else {
      printf("unexpected import '%.*s'\n", (int)import_name->size, import_name->data);
      return false;
    }
  }
  wasm_importtype_vec_delete(&import_types);

  wasm_trap_t *trap = NULL;
  wasm_instance_t *instance = wasm_instance_new(self->store, module, &imports, &trap);
  if (trap) {
    wasm_message_t message;
    wasm_trap_message(trap, &message);
    printf("error loading wasm: %s\n", message.data);
    abort();
  }

  wasm_extern_vec_t exports = WASM_EMPTY_VEC;
  wasm_exporttype_vec_t export_types = WASM_EMPTY_VEC;
  wasm_module_exports(module, &export_types);
  wasm_instance_exports(instance, &exports);
  assert(export_types.size == exports.size);
  printf("export count: %lu\n", export_types.size);

  wasm_extern_t *language_extern = NULL;
  for (unsigned i = 0; i < exports.size; i++) {
    wasm_extern_t *export = exports.data[i];
    wasm_exporttype_t *export_type = export_types.data[i];
    const wasm_name_t *name = wasm_exporttype_name(export_type);
    printf("  export name: %.*s\n", (int)name->size, name->data);

    // Update pointers to reflect memory and function table offsets.
    if (name_eq(name, "__wasm_apply_data_relocs")) {
      wasm_func_t *apply_relocation_func = wasm_extern_as_func(export);
      wasm_val_vec_t arguments = WASM_EMPTY_VEC;
      wasm_val_vec_t results = WASM_EMPTY_VEC;
      wasm_trap_t *trap = wasm_func_call(apply_relocation_func, &arguments, &results);
      if (trap) {
        wasm_message_t message;
        wasm_trap_message(trap, &message);
        printf("error calling relocation function: %s\n", message.data);
        abort();
      }
    } else if (name_eq(name, language_function_name)) {
      language_extern = export;
    }
  }
  wasm_exporttype_vec_delete(&export_types);

  if (!language_extern) {
    printf("failed to find function %s\n", language_function_name);
    abort();
  }

  wasm_func_t *language_func = wasm_extern_as_func(language_extern);
  wasm_val_vec_t arguments = WASM_EMPTY_VEC;
  wasm_val_vec_t results = WASM_EMPTY_VEC;
  wasm_val_vec_new_uninitialized(&results, 1);
  trap = wasm_func_call(language_func, &arguments, &results);
  if (trap) {
    wasm_message_t message;
    wasm_trap_message(trap, &message);
    printf("error calling language function: %s\n", message.data);
    abort();
  }

  wasm_val_t language_address_val = results.data[0];
  assert(language_address_val.kind == WASM_I32);

  *result = instance;
  *language_address = language_address_val.of.i32;
  return true;
}

TSWasmLanguage *ts_wasm_store_load_language(
  TSWasmStore *self,
  const char *language_name,
  const char *wasm,
  uint32_t wasm_len
) {
  // Instantiate module.
  wasm_byte_vec_t file = {.size = wasm_len, .data = (char *)wasm};
  wasm_module_t *module = wasm_module_new(self->store, &file);

  wasm_instance_t *instance;
  int32_t language_address;
  if (!ts_wasm_store__instantiate(self, module, language_name, &instance, &language_address)) return NULL;

  LanguageInWasmMemory wasm_language;
  const byte_t *memory = wasm_memory_data(self->memory);
  memcpy(&wasm_language, &memory[language_address], sizeof(LanguageInWasmMemory));

  TSLanguage *language = ts_malloc(sizeof(TSLanguage));
  StringData symbol_name_buffer = array_new();
  StringData field_name_buffer = array_new();

  *language = (TSLanguage) {
    .version = wasm_language.version,
    .symbol_count = wasm_language.symbol_count,
    .alias_count = wasm_language.alias_count,
    .token_count = wasm_language.token_count,
    .external_token_count = wasm_language.external_token_count,
    .state_count = wasm_language.state_count,
    .large_state_count = wasm_language.large_state_count,
    .production_id_count = wasm_language.production_id_count,
    .field_count = wasm_language.field_count,
    .max_alias_sequence_length = wasm_language.max_alias_sequence_length,
    .keyword_capture_token = wasm_language.keyword_capture_token,
    .parse_table = copy(
      &memory[wasm_language.parse_table],
      wasm_language.large_state_count * wasm_language.symbol_count * sizeof(uint16_t)
    ),
    .parse_actions = copy(
      &memory[wasm_language.parse_actions],
      3000 // TODO - determine number of parse actions
    ),
    .symbol_names = copy_strings(
      memory,
      wasm_language.symbol_names,
      wasm_language.symbol_count,
      &symbol_name_buffer
    ),
    .symbol_metadata = copy(
      &memory[wasm_language.symbol_metadata],
      wasm_language.symbol_count * sizeof(TSSymbolMetadata)
    ),
    .public_symbol_map = copy(
      &memory[wasm_language.public_symbol_map],
      wasm_language.symbol_count * sizeof(TSSymbol)
    ),
    .lex_modes = copy(
      &memory[wasm_language.lex_modes],
      wasm_language.state_count * sizeof(TSLexMode)
    ),
  };

  if (language->field_count > 0 && language->production_id_count > 0) {
    language->field_map_slices = copy(
      &memory[wasm_language.field_map_slices],
      wasm_language.production_id_count * sizeof(TSFieldMapSlice)
    );
    const TSFieldMapSlice last_field_map_slice = language->field_map_slices[language->production_id_count - 1];
    language->field_map_entries = copy(
      &memory[wasm_language.field_map_entries],
      (last_field_map_slice.index + last_field_map_slice.length) * sizeof(TSFieldMapEntry)
    );
    language->field_names = copy_strings(
      memory,
      wasm_language.field_names,
      wasm_language.field_count,
      &field_name_buffer
    );
  }

  if (language->alias_count > 0 && language->production_id_count > 0) {
    // The alias map contains symbols, alias counts, and aliases, terminated by a null symbol.
    int32_t alias_map_size = 0;
    for (;;) {
      TSSymbol symbol;
      memcpy(&symbol, &memory[wasm_language.alias_map + alias_map_size], sizeof(symbol));
      alias_map_size += sizeof(TSSymbol);
      if (symbol == 0) break;
      uint16_t value_count;
      memcpy(&value_count, &memory[wasm_language.alias_map + alias_map_size], sizeof(value_count));
      alias_map_size += value_count * sizeof(TSSymbol);
    }
    language->alias_map = copy(
      &memory[wasm_language.alias_map],
      alias_map_size
    );
    language->alias_sequences = copy(
      &memory[wasm_language.alias_sequences],
      wasm_language.production_id_count * wasm_language.max_alias_sequence_length * sizeof(TSSymbol)
    );
  }

  if (language->state_count > language->large_state_count) {
    uint32_t small_state_count = wasm_language.state_count - wasm_language.large_state_count;
    language->small_parse_table_map = copy(
      &memory[wasm_language.small_parse_table_map],
      small_state_count * sizeof(uint32_t)
    );
    uint32_t index = language->small_parse_table_map[small_state_count - 1];
    language->small_parse_table = copy(
      &memory[wasm_language.small_parse_table],
      (index + 64) * sizeof(uint16_t) // TODO - determine actual size
    );
  }

  TSWasmLanguage *result = ts_malloc(sizeof(TSWasmLanguage));
  *result = (TSWasmLanguage) {
    .id = atomic_inc(&NEXT_LANGUAGE_ID),
    .ref_count = 1,
    .module = wasm_module_share(module),
    .language = language,
    .symbol_name_buffer = symbol_name_buffer.contents,
    .field_name_buffer = field_name_buffer.contents,
  };
  array_push(&self->language_instances, ((LanguageInstance) {
    .instance = instance,
    .external_scan_index = wasm_language.external_scanner.scan,
    .keyword_lex_fn_index = wasm_language.keyword_lex_fn,
    .main_lex_fn_index = wasm_language.lex_fn,
  }));
  return result;
}

bool ts_wasm_store_start(TSWasmStore *self, TSLexer *lexer, const TSWasmLanguage *language) {
  uint32_t instance_index = 0;
  bool exists = false;
  array_search_sorted_by(&self->language_instances, .id, language->id, &instance_index, &exists);

  if (!exists) {
    wasm_module_t *module = wasm_module_obtain(self->store, language->module);
    wasm_instance_t *instance;
    int32_t language_address;
    if (!ts_wasm_store__instantiate(self, module, language->name, &instance, &language_address)) {
      return false;
    }

    LanguageInWasmMemory wasm_language;
    const byte_t *memory = wasm_memory_data(self->memory);
    memcpy(&wasm_language, &memory[language_address], sizeof(LanguageInWasmMemory));
    array_insert(&self->language_instances, instance_index, ((LanguageInstance) {
      .id = language->id,
      .instance = instance,
      .main_lex_fn_index = wasm_language.lex_fn,
      .keyword_lex_fn_index = wasm_language.keyword_lex_fn,
    }));
  }

  self->current_lexer = lexer;
  self->current_instance = &self->language_instances.contents[instance_index];
  return true;
}

void ts_wasm_store_stop(TSWasmStore *self) {
  self->current_lexer = NULL;
  self->current_instance = NULL;
}